/**
 * @file Ball.h
 * @author Sohum Jain
 *
 * Class describes a ball
 */

#ifndef BALL_H
#define BALL_H

#include "Item.h"

/**
 * The ball in the game
 */
class Ball : public Item
{
private:

public:
    /**
     * Constructor
     * @param game The Spartanoid game this ball belongs to
     * @param filename Image filename for this ball
     */
    Ball(Spartanoid* game, const std::wstring& filename);

    /**
     * Update the ball state.
     * @param elapsed Time since the last update in seconds
     */
    void Update(double elapsed) override;

    /**
     * Handle a mouse click on the ball.
     */
    void OnClick() override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBall(this); }
};

#endif