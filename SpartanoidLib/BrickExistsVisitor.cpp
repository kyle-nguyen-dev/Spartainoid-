/**
 * @file BrickExistsVisitor.cpp
 * @author Nick Tokarz
 */

#include "pch.h"
#include "BrickExistsVisitor.h"

/**
 * set flag saying there is a brick
 * @param brick the brick visited
 */
void BrickExistsVisitor::VisitBrick(Brick* brick)
{
    mBrickExists = true;
}