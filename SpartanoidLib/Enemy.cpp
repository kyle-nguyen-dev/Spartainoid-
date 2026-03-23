/**
 * @file Enemy.cpp
 * @author Sam Nowlan
 */

#include "pch.h"
#include "Enemy.h"

#include <wx/graphics.h>

#include "Ball.h"
#include "Spartanoid.h"

/**
 * Constructor
 * @param game The Spartanoid game this enemy belongs to
 * @param filename Image filename
 */
Enemy::Enemy(Spartanoid* game, const std::wstring& filename)
    : Item(game, filename)
{
    SetSize(mItemBitmap->GetWidth(), mItemBitmap->GetHeight());

    // Move horizontally
    SetVelocity(150, 0);
}

/**
 * Update enemy movement.
 * Moves horizontally and bounces off screen edges.
 *
 * @param elapsed Time since last update in seconds
 */
void Enemy::Update(double elapsed)
{
    Item::Update(elapsed);

    // Bounce off left wall
    if (GetX() - GetWidth() / 2 <= 0)
    {
        SetPosition(GetWidth() / 2, GetY());
        SetVelocity(-GetVelocityX(), GetVelocityY());
    }

    // Bounce off right wall
    if (GetX() + GetWidth() / 2 >= GetSpartanoid()->GetWidth())
    {
        SetPosition(GetSpartanoid()->GetWidth() - GetWidth() / 2, GetY());
        SetVelocity(-GetVelocityX(), GetVelocityY());
    }
}

/**
 * Draw the enemy.
 * The sprite is mirrored depending on movement direction.
 *
 * @param graphics Graphics context used for drawing
 */
void Enemy::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // If moving left, mirror the sprite
    if (GetVelocityX() > 0)
    {
        graphics->Translate(GetX(), 0);
        graphics->Scale(-1, 1);

        graphics->DrawBitmap(
            *mItemBitmap,
            -GetWidth() / 2,
            GetY() - GetHeight() / 2,
            GetWidth(),
            GetHeight()
        );
    }
    else
    {
        graphics->DrawBitmap(
            *mItemBitmap,
            GetX() - GetWidth() / 2,
            GetY() - GetHeight() / 2,
            GetWidth(),
            GetHeight()
        );
    }

    graphics->PopState();
}

/**
 * Handle collision with a ball.
 * The ball is removed and the game enters a lose state.
 *
 * @param ball The ball that hit this enemy
 */
void Enemy::HitByBall(Ball* ball)
{
    ball->SetActive(false);
    GetSpartanoid()->SetGameOver(true);
}