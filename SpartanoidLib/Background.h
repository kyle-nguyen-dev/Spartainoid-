/**
 * @file Background.h
 * @author Nick Tokarz
 *
 * Class representing a background image item
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H

#include "Item.h"

/**
 * Class representing a background image
 */
class Background : public Item
{
public:
    /**
     * Constructor
     * @param game The Spartanoid game
     * @param filename The image filename
     */
    Background(Spartanoid* game, const std::wstring& filename)
        : Item(game, filename) {}

    /**
     * Handles collision with background always false
     * @param item items colliding with background
     * @return false
     */
    bool CollisionTest(Item* item) override {return false;};

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBackground(this); }
};

#endif //PROJECT1_BACKGROUND_H