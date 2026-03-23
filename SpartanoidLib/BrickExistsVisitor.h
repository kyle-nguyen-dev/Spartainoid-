/**
 * @file BrickExistsVisitor.h
 * @author Nick Tokarz
 *
 *  Class Describes Brick exists visitor
 */

#ifndef PROJECT1_BRICKEXISTSVISITOR_H
#define PROJECT1_BRICKEXISTSVISITOR_H

#include "ItemVisitor.h"

/**
 * class describes brick exists visitor
 */
class BrickExistsVisitor : public ItemVisitor
{
private:
    /// Tells if brick exists
    bool mBrickExists = false;
public:
    void VisitBrick(Brick* brick) override;

    /**
     * Tells if a brick exists
     * @return true if brick exists
     */
    bool BrickExists() const { return mBrickExists; }
};

#endif //PROJECT1_BRICKEXISTSVISITOR_H