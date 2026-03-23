/**
 * @file Brick.cpp
 * @author Nick Tokarz
 */

#include "pch.h"
#include "Brick.h"
#include "Ball.h"
#include "Coin.h"
#include "Spartanoid.h"
#include "Level.h"
#include <cstdlib>

using namespace std;

/**
 * Constructor
 * @param spartanoid The Spartanoid game this brick belongs to
 * @param filename The image filename for this brick
 */
Brick::Brick(Spartanoid *spartanoid, const std::wstring& filename) : Item(spartanoid, filename)
{
    SetSize(mItemBitmap->GetWidth(), mItemBitmap->GetHeight());
}

/**
 * Handle collision with a ball.
 * Deactivates the brick, reflects the ball, awards score,
 * and may spawn a coin.
 *
 * @param ball The ball that hit this brick
 */
void Brick::HitByBall(Ball* ball)
{
    SetActive(false);

    double ballLeft   = ball->GetX() - ball->GetWidth()/2;
    double ballRight  = ball->GetX() + ball->GetWidth()/2;
    double ballTop    = ball->GetY() - ball->GetHeight()/2;
    double ballBottom = ball->GetY() + ball->GetHeight()/2;

    double brickLeft   = GetX() - GetWidth()/2;
    double brickRight  = GetX() + GetWidth()/2;
    double brickTop    = GetY() - GetHeight()/2;
    double brickBottom = GetY() + GetHeight()/2;

    double overlapLeft   = ballRight - brickLeft;
    double overlapRight  = brickRight - ballLeft;
    double overlapTop    = ballBottom - brickTop;
    double overlapBottom = brickBottom - ballTop;

    double minOverlapX = std::min(overlapLeft, overlapRight);
    double minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY)
    {
        // Hit left or right side
        ball->SetVelocity(-ball->GetVelocityX(), ball->GetVelocityY());
    }
    else
    {
        // Hit top or bottom
        ball->SetVelocity(ball->GetVelocityX(), -ball->GetVelocityY());
    }

    GetSpartanoid()->GetScoreBoard().AddScore(10);

    // 20% chance to spawn a coin
    auto level = GetSpartanoid()->GetLevel();
    if (level->HasCoin() && (rand() % 100) < 20)
    {
        auto coin = std::make_shared<Coin>(
            GetSpartanoid(),
            level->GetCoinImage(),
            level->GetCoinFrames(),
            level->GetCoinValue()
        );

        // Spawn at brick center, launched with ball's velocity
        coin->SetPosition(GetX(), GetY());
        coin->SetVelocity(ball->GetVelocityX(), ball->GetVelocityY());

        GetSpartanoid()->Add(coin);
    }
}