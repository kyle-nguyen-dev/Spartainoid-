/**
 * @file Coin.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Coin.h"
#include "Spartanoid.h"
#include "Paddle.h"
#include <wx/graphics.h>

/**
 * Constructor
 *
 * Loads all animation frames from disk. Given a base image such as
 * "images/coin-0.png", this loads:
 * coin-0.png, coin-1.png, ..., coin-(frames-1).png
 *
 * @param game The Spartanoid game this coin belongs to
 * @param baseImage Base filename for the animation frames
 * @param frames Number of animation frames
 * @param value Score value of the coin
 */
Coin::Coin(Spartanoid* game,
           const std::wstring& baseImage,
           int frames,
           int value)
    : Item(game, baseImage), mValue(value)
{

    std::wstring path = baseImage;

    size_t dashPos = path.rfind(L'-');
    size_t dotPos  = path.rfind(L'.');

    std::wstring prefix = path.substr(0, dashPos + 1);
    std::wstring suffix = path.substr(dotPos);

    for (int i = 0; i < frames; i++)
    {
        std::wstring framePath = prefix + std::to_wstring(i) + suffix;
        auto img = std::make_shared<wxImage>(framePath, wxBITMAP_TYPE_ANY);
        auto bmp = std::make_shared<wxBitmap>(*img);
        mImages.push_back(img);
        mFrames.push_back(bmp);
    }

    if (!mFrames.empty())
    {
        SetSize(mFrames[0]->GetWidth(), mFrames[0]->GetHeight());
    }
}

/**
 * Update the coin each frame.
 * Advances the animation, applies gravity, bounces off side walls,
 * awards score if collected by the paddle, and deactivates if it
 * falls below the screen.
 *
 * @param elapsed Time since the last frame in seconds
 */
void Coin::Update(double elapsed)
{
    if (!IsActive())
        return;

    mFrameTime += elapsed;
    if (mFrameTime >= FrameDuration)
    {
        mFrameTime -= FrameDuration;
        mCurrentFrame = (mCurrentFrame + 1) % static_cast<int>(mFrames.size());
    }

    SetVelocity(GetVelocityX(), GetVelocityY() + Gravity * elapsed);

    Item::Update(elapsed);

    if (GetX() - GetWidth() / 2 <= 0)
    {
        SetPosition(GetWidth() / 2, GetY());
        SetVelocity(-GetVelocityX(), GetVelocityY());
    }
    if (GetX() + GetWidth() / 2 >= GetSpartanoid()->GetWidth())
    {
        SetPosition(GetSpartanoid()->GetWidth() - GetWidth() / 2, GetY());
        SetVelocity(-GetVelocityX(), GetVelocityY());
    }

    auto paddle = GetSpartanoid()->GetPaddle();

    if (paddle)
    {
        auto itemLeft   = paddle->GetX() - paddle->GetWidth() / 2;
        auto itemRight  = paddle->GetX() + paddle->GetWidth() / 2;
        auto itemTop    = paddle->GetY() - paddle->GetHeight() / 2;
        auto itemBottom = paddle->GetY() + paddle->GetHeight() / 2;

        auto ourLeft   = GetX() - GetWidth() / 2;
        auto ourRight  = GetX() + GetWidth() / 2;
        auto ourTop    = GetY() - GetHeight() / 2;
        auto ourBottom = GetY() + GetHeight() / 2;

        if (!(ourRight < itemLeft ||
              ourLeft > itemRight ||
              ourTop > itemBottom ||
              ourBottom < itemTop))
        {
            // Add score
            GetSpartanoid()->GetScoreBoard().AddScore(mValue);

            // Remove coin
            SetActive(false);
        }
    }

    if (GetY() - GetHeight() / 2 > GetSpartanoid()->GetHeight())
    {
        SetActive(false);
    }
}

/**
 * Draw the current animation frame centered on the coin's position.
 * @param gc Graphics context
 */
void Coin::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (!IsActive() || mFrames.empty())
        return;

    gc->DrawBitmap(
        *mFrames[mCurrentFrame],
        GetX() - GetWidth() / 2.0,
        GetY() - GetHeight() / 2.0,
        GetWidth(),
        GetHeight()
    );
}