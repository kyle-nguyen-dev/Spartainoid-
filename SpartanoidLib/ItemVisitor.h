/**
 * @file ItemVisitor.h
 * @author Nick Tokarz
 *
 * Describes base class of item visitor
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class Ball;
class Paddle;
class Brick;
class Background;
class Enemy;
class PowerUp;
class Coin;

/**
 * Describes base class of item visitor
 */
class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}
private:

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit a ball
     * @param ball visited
     */
    virtual void VisitBall(Ball* ball) {}

    /**
     * Visit a paddle
     * @param paddle visited
     */
    virtual void VisitPaddle(Paddle* paddle) {}

    /**
     * Visit a brick
     * @param brick visited
     */
    virtual void VisitBrick(Brick* brick) {}

    /**
     * Visit a background
     * @param background visited
     */
    virtual void VisitBackground(Background* background) {}

    /**
     * Visit an enemy
     * @param enemy being visited
     */
    virtual void VisitEnemy(Enemy* enemy) {}

    /**
     * Visit a power up
     * @param powerUp being visited
     */
    virtual void VisitPowerUp(PowerUp* powerUp) {}

    /**
     * Visit a coin
     * @param coin being visited
     */
    virtual void VisitCoin(Coin* coin) {}
};

#endif //PROJECT1_ITEMVISITOR_H