/**
 * @file Brick.h
 * @author Nick Tokarz
 *
 * Class that describes a brick in the Spartanoid game.
 */

#ifndef PROJECT1_BRICK_H
#define PROJECT1_BRICK_H
#include "Item.h"

/**
 * Brick item Class
 */
class Brick : public Item
{
public:
    /**
     * Constructor
     * @param spartanoid The Spartanoid game this brick belongs to
     * @param filename Image filename for this brick
     */
    Brick(Spartanoid* spartanoid, const std::wstring& filename);

    /**
     * Handle collision with a ball.
     * @param ball The ball that hit this brick
     */
    void HitByBall(Ball* ball) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBrick(this); }
};

#endif //PROJECT1_BRICK_H