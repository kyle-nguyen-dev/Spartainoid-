/**
 * @file BallOutVisitor.h
 * @author Sohum Jain
 *
 * Class describes ball out visitor
 */

#ifndef PROJECT1_BALLOUTVISITOR_H
#define PROJECT1_BALLOUTVISITOR_H

#include "ItemVisitor.h"

/**
 * Class describes ball out visitor
 */
class BallOutVisitor : public ItemVisitor
{
private:
    ///Bool for if there is a ball in play
    bool mBallIn = false;

public:
    /**
     * Visit a ball item.
     * @param ball The ball being visited
     */
    void VisitBall(Ball* ball) override;

    /**
     * Returns if there is a ball active
     * @return ball is in bool
     */
    bool IsBallIn() const { return mBallIn; }
};

#endif //PROJECT1_BALLOUTVISITOR_H