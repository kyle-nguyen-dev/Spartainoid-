/**
 * @file Paddle.h
 * @author Sohum Jain
 *
 * Class for the paddle
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "Item.h"

/**
 * The paddle used to bounce the ball in the game
 */
class Paddle : public Item
{
private:
    /// Base movement speed of the paddle
    double mBaseSpeed = 6.0;

    /// Multiplier applied to the base speed
    double mSpeedMultiplier = 1.0;

public:
    /**
     * Constructor
     * @param game The Spartanoid game this paddle belongs to
     * @param filename Image filename for the paddle
     */
    Paddle(Spartanoid* game, const std::wstring& filename);

    /**
     * Move the paddle left.
     */
    void MoveLeft();

    /**
     * Move the paddle right.
     */
    void MoveRight();

    /**
     * Handle collision with a ball.
     * @param ball The ball that hit the paddle
     */
    void HitByBall(Ball* ball) override;

    /**
     * Handle collision with a coin.
     * @param coin The coin that hit the paddle
     */
    void HitByCoin(Coin* coin) override;

    /**
     * Set the paddle speed multiplier.
     * @param multiplier Speed multiplier value
     */
    void SetSpeedMultiplier(double multiplier) { mSpeedMultiplier = multiplier; }

    /**
     * Get the current paddle speed.
     * @return Paddle movement speed
     */
    double GetSpeed() const { return mBaseSpeed * mSpeedMultiplier; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPaddle(this); }

};

#endif