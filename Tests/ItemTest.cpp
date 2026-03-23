/**
 * @file ItemTest.cpp
 * @author Nick Tokarz
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Spartanoid.h>

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Spartanoid *game) : Item(game, L"images/lifebuoy.png") {}


};

TEST(ItemTest, Construct) {
    Spartanoid game;
    ItemMock item(&game);
}

TEST(ItemTest, GettersSetters){
    Spartanoid game;
    ItemMock item(&game);

    // Test SetLocation, GetX, and GetY
    item.SetPosition(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);
}