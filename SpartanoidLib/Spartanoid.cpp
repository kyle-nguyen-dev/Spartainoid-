/**
 * @file Spartanoid.cpp
 * @author Sohum Jain
 * @author Sam Nowlan
 */

#include "pch.h"
#include "Spartanoid.h"
#include "Paddle.h"
#include "Ball.h"
#include "Item.h"

#include <wx/graphics.h>
#include <wx/xml/xml.h>
#include <map>

#include "Brick.h"
#include "BallOutVisitor.h"
#include <algorithm>

#include "BrickExistsVisitor.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Spartanoid::Update(double elapsed)
{
    for (auto item : mItems)
    {
        if (item->IsActive())
            item->Update(elapsed);
    }

    mItems.erase(
        std::remove_if(mItems.begin(), mItems.end(),
            [](std::shared_ptr<Item> item)
            {
                return !item->IsActive();
            }),
        mItems.end()
    );

    for (auto& item : mPendingItems)
    {
        mItems.push_back(item);
    }
    mPendingItems.clear();

    mScoreBoard.Update(elapsed);

    BallOutVisitor visitorBallOut;

    for (auto item : mItems)
    {
        item->Accept(&visitorBallOut);
    }

    if (!(visitorBallOut.IsBallIn()))
    {
        mGameOver = true;
    }
    BrickExistsVisitor visitorBrickExists;

    for (auto item : mItems)
    {
        item->Accept(&visitorBrickExists);
    }
    if (!visitorBrickExists.BrickExists())
    {
        mGameWon = true;
    }

    if (mGameOver)
    {
        mGameOverTime += elapsed;

        if (mGameOverTime >= GameOverDelay)
        {
            LoadLevel(mCurrentLevel);
        }
        return;
    }

    if (mGameWon)
    {
        mGameWonTime += elapsed;

        if (mGameWonTime >= GameWonDelay)
        {
            LoadLevel(mCurrentLevel);
        }
        return;
    }

}

/**
 * Draw the spartanoid game
 * @param graphics The device context to draw on
 */
void Spartanoid::Draw(shared_ptr<wxGraphicsContext> gc, int width, int height)
{
    mScale = double(height) / double(Height);
    gc->Scale(mScale, mScale);

    mVirtualWidth = (double)width/mScale;

    gc->PushState();

    for (auto item : mItems)
    {
        if (item->IsActive())
            item->Draw(gc);
    }
    mScoreBoard.Draw(gc);

    if (mGameOver && !mGameWon)
    {
        wxFont font(wxSize(0, 80),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);

        gc->SetFont(font, *wxBLACK);
        gc->DrawText(L"You Lose!", mWidth / 2 - 200 + 3, mHeight / 2 - 40 + 3);

        gc->SetFont(font, *wxRED);
        gc->DrawText(L"You Lose!", mWidth / 2 - 200, mHeight / 2 - 40);
    }
    if (mGameWon)
    {
        wxFont font(wxSize(0, 80),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);

        gc->SetFont(font, *wxBLACK);
        gc->DrawText(L"You Win!", mWidth / 2 - 200 + 3, mHeight / 2 - 40 + 3);

        gc->SetFont(font, *wxGREEN);
        gc->DrawText(L"You Win!", mWidth / 2 - 200, mHeight / 2 - 40);
    }

    gc->PopState();

}

/**
 * Moves paddle left
 */
void Spartanoid::MovePaddleLeft()
{
    mPaddle->MoveLeft();
}

/**
 * Moves paddle right
 */
void Spartanoid::MovePaddleRight()
{
    mPaddle->MoveRight();
}

/**
 * Constructor
 */
Spartanoid::Spartanoid() : mScoreBoard(1024)
{
    mLevels.push_back(std::make_shared<Level>(0));
    mLevels.push_back(std::make_shared<Level>(1));
    mLevels.push_back(std::make_shared<Level>(2));
    mLevels.push_back(std::make_shared<Level>(3));

    mLevel = 1;
    LoadLevel(1);

}
/**
 * Loads the Level
 */
void Spartanoid::LoadLevel(int levelNumber)
{
    mCurrentLevel = levelNumber;

    Clear();

    mWidth = mLevels[levelNumber]->GetWidth();
    mHeight = mLevels[levelNumber]->GetHeight();

    mScoreBoard.SetWidth(mWidth);
    mScoreBoard.Reset();

    mGameOver = false;
    mGameOverTime = 0.0;

    mGameWon = false;
    mGameWonTime = 0.0;

    mLevels[levelNumber]->PopulateItems(this, mItems, mPaddle);

    if (mPaddle)
        mPaddle->SetSpeedMultiplier(mPaddleSpeedMultiplier);

}

/**
 * Add an item to the spartanoid
 * @param item New item to add
 */
void Spartanoid::Add(std::shared_ptr<Item> item)
{
    mPendingItems.push_back(item);
}

/**
 * Clears items from spartanoid
 *
 */
void Spartanoid::Clear()
{
    mItems.clear();
    mPendingItems.clear();
}

/**
 * Changes the speed of paddle
 * @param ia double with value of multiplier
 */
void Spartanoid::SetPaddleSpeedMultiplier(double multiplier)
{
    mPaddleSpeedMultiplier = multiplier;

    if (mPaddle)
    {
        mPaddle->SetSpeedMultiplier(multiplier);
    }
}
