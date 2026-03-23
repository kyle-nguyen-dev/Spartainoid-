/**
 * @file Enemy.h
 * @author Sam Nowlan
 *
 * Class describes an enemy
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Item.h"

/**
 * Enemy that moves
 */
class Enemy : public Item
{
public:
    /**
     * Constructor
     * @param game The Spartanoid game this enemy belongs to
     * @param filename Image filename for this enemy
     */
    Enemy(Spartanoid* game, const std::wstring& filename);

    /**
     * Update the enemy movement.
     * @param elapsed Time since the last update in seconds
     */
    void Update(double elapsed) override;

    /**
     * Draw the enemy.
     * @param graphics Graphics context used for drawing
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Handle collision with a ball.
     * @param ball The ball that hit this enemy
     */
    void HitByBall(Ball* ball) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitEnemy(this); }
};

#endif // ENEMY_H