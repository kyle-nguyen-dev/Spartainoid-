/**
 * @file BallOutVisitor.cpp
 * @author Sohum Jain
 */

#include "pch.h"
#include "BallOutVisitor.h"
#include "Ball.h"
#include "Spartanoid.h"

/**
 * Visit a ball and determine if it is still in play.
 * A ball is considered active if it has not fallen below the screen.
 *
 * @param ball The ball being visited
 */
void BallOutVisitor::VisitBall(Ball* ball)
{
    int screenHeight = ball->GetSpartanoid()->GetHeight();

    // Check if the ball is still within the visible screen bounds
    if (!(ball->GetY() + ball->GetHeight() / 2 > screenHeight))
    {
        mBallIn = true;
    }
}