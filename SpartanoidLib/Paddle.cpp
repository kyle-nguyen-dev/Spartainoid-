/**
 * @file Paddle.cpp
 * @author Sohum Jain
 */

#include "pch.h"
#include "Paddle.h"
#include <wx/graphics.h>

#include "Ball.h"
#include "Coin.h"
#include "Spartanoid.h"

/**
 * Constructor
 * @param game The Spartanoid game this paddle belongs to
 * @param filename Image filename for the paddle
 */
Paddle::Paddle(Spartanoid* game, const std::wstring& filename)
    : Item(game, filename)
{
    mItemImage = std::make_unique<wxImage>(
        L"images/lifebuoy.png", wxBITMAP_TYPE_ANY);

    mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);

    SetSize(mItemBitmap->GetWidth(), mItemBitmap->GetHeight());
    SetPosition(400, 650);
}

/**
 * Move the paddle to the left
 */
void Paddle::MoveLeft()
{
    double newX = GetX() - GetSpeed();
    if (newX < GetWidth() / 2)
        newX = GetWidth() / 2;

    SetPosition(newX, GetY());
}

/**
 * Move the paddle to the right
 */
void Paddle::MoveRight()
{
    double newX = GetX() + GetSpeed();
    if (newX > GetSpartanoid()->GetWidth() - GetWidth()/2)
        newX = GetSpartanoid()->GetWidth() - GetWidth()/2;

    SetPosition(newX, GetY());
}

/**
 * Handle collision with a ball.
 * The bounce angle depends on where the ball hits the paddle.
 *
 * @param ball The ball that hit the paddle
 */
void Paddle::HitByBall(Ball* ball)
{
    // Distance from paddle center to ball center
    double x = ball->GetX() - GetX();

    // Paddle width
    double l = GetWidth();

    // Compute coefficient
    double coefficient = (2 * x) / l;

    // Clamp to [-1, 1]
    coefficient = std::max(-1.0, std::min(1.0, coefficient));

    // Maximum bounce angle (60 degrees)
    double maxAngle = 60.0 * M_PI / 180.0;

    // Compute reflection angle
    double angle = coefficient * maxAngle;

    // Ball speed
    double speed = sqrt(ball->GetV().X() * ball->GetV().X() +
                    ball->GetV().Y() * ball->GetV().Y());

    /// Scale speed slightly based on hit position
    double minSpeedFactor = 0.90;
    double maxSpeedFactor = 1.15;
    double speedFactor = minSpeedFactor + (maxSpeedFactor - minSpeedFactor) * std::abs(coefficient);

    double scaledSpeed = speed * speedFactor;

    // Compute new velocity
    double vx = scaledSpeed * sin(angle);
    double vy = -scaledSpeed * cos(angle);

    ball->SetVelocity(vx, vy);
}

/**
 * Handles when coin hits paddle
 * @param coin Coin hitting paddle
 */
void Paddle::HitByCoin(Coin* coin)
{
    coin->SetActive(false);
    GetSpartanoid()->GetScoreBoard().AddScore(coin->GetValue());
}