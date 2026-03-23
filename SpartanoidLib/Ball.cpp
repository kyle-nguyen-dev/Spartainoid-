/**
 * @file Ball.cpp
 * @author Sohum Jain
 * @author Sam Nowlan
 */

#include "pch.h"
#include "Ball.h"
#include <wx/graphics.h>

#include "Paddle.h"
#include "Spartanoid.h"

#include "Brick.h"
#include "Level.h"
#include "Enemy.h"

/**
 * Constructor
 * @param game The Spartanoid game this ball belongs to
 * @param filename the filename of ball image
 */
Ball::Ball(Spartanoid* game, const std::wstring& filename)
    : Item(game, filename)
{
    SetSize(mItemBitmap->GetWidth(), mItemBitmap->GetHeight());

    SetVelocity(0, 0);
}

/**
 * Update the ball position and handle collisions
 * @param elapsed Time elapsed since the last update
 */
void Ball::Update(double elapsed)
{
    if (!IsActive())
    {
        return;
    }

    Item::Update(elapsed);

    // Wall collision — X,Y is center of ball
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

    if (GetY() - GetHeight() / 2 <= 0)
    {
        SetPosition(GetX(), GetHeight() / 2);
        SetVelocity(GetVelocityX(), -GetVelocityY());
    }

    Vector previousVector = GetV();

    // Item collision
    for (auto item : GetSpartanoid()->GetItems())
    {
        if (!item->IsActive())
            continue;

        if (item.get() == this)  // skip self
            continue;

        if (item->CollisionTest(this))
        {
            // Collision detected
            item->HitByBall(this);

            if (previousVector.X() != GetV().X() || previousVector.Y() != GetV().Y())
            {
                break;
            }
        }
    }
}

/**
 * Tells ball to start moving when the screen is clicked
 */
void Ball::OnClick()
{
    if (GetV().X() == 0 && GetV().Y() == 0)
    {
        SetVelocity(30, -500);
    }
}