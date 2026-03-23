/**
 * @file PowerUp.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "PowerUp.h"
#include "Ball.h"
#include "Spartanoid.h"
#include <wx/graphics.h>

/**
 * Constructor
 * @param game Pointer to the Spartanoid game
 * @param filename Image filename for this power-up
 */
PowerUp::PowerUp(Spartanoid* game, const std::wstring& filename)
    : Item(game, filename)
{
    mOriginalWidth  = GetWidth();
    mOriginalHeight = GetHeight();
}

/**
 * Update the power-up each frame.
 * If consumed, advances the shrink + text animation.
 * Deactivates itself when the animation finishes.
 * @param elapsed Seconds since last frame
 */
void PowerUp::Update(double elapsed)
{
    if (!mConsumed)
        return;

    mConsumedTime += elapsed;
    double progress = mConsumedTime / AnimationDuration;

    if (progress >= 1.0)
    {
        SetActive(false);
        return;
    }

    mScale = 1.0 - progress;

    mTextY = GetY() - (progress * 120.0);

    mTextSize = 20.0 + progress * 40.0;
}

/**
 * Draw the power-up (shrinking image) and the floating "Power Up!" text.
 * @param gc Graphics context
 */
void PowerUp::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (!IsActive())
        return;

    if (!mConsumed)
    {
        gc->DrawBitmap(
            *mItemBitmap,
            GetX() - GetWidth() / 2.0,
            GetY() - GetHeight() / 2.0,
            GetWidth(),
            GetHeight()
        );
    }
    else
    {
        double drawW = mOriginalWidth  * mScale;
        double drawH = mOriginalHeight * mScale;

        if (drawW > 0 && drawH > 0)
        {
            gc->DrawBitmap(
                *mItemBitmap,
                GetX() - drawW / 2.0,
                GetY() - drawH / 2.0,
                drawW,
                drawH
            );
        }

        int fontSize = static_cast<int>(mTextSize);
        wxFont font(wxSize(0, fontSize),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);


        gc->SetFont(font, *wxBLACK);
        gc->DrawText("Power Up!", GetX() - 60 + 2, mTextY + 2);


        gc->SetFont(font, wxColour(255, 220, 0));
        gc->DrawText("Power Up!", GetX() - 60, mTextY);
    }
}

/**
 * Called when the ball collides with this power-up.
 * Doubles the score, spawns a second ball, and starts the animation.
 * @param ball The ball that hit this power-up
 */
void PowerUp::HitByBall(Ball* ball)
{
    if (mConsumed)
        return;

    mConsumed = true;
    mTextY = GetY();


    GetSpartanoid()->GetScoreBoard().DoubleScore();

    auto newBall = std::make_shared<Ball>(
        GetSpartanoid(),
        L"images/ball.png"
    );

    newBall->SetPosition(ball->GetX(), ball->GetY());
    newBall->SetVelocity(-ball->GetVelocityX(), ball->GetVelocityY());
    GetSpartanoid()->Add(newBall);
}