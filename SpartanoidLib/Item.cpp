/**
 * @file Item.cpp
 * @author Sam Nowlan
 */

#include "pch.h"
#include "Item.h"
#include "Spartanoid.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor
 * @param spartanoid item
 * @param filename The file to display for this item
 */
Item::Item(Spartanoid *spartanoid, const std::wstring &filename) : mSpartanoid(spartanoid)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
    SetSize(mItemImage->GetWidth(), mItemImage->GetHeight());
}

/**
 * Update the item
 * @param elapsed Time since last update
 */
void Item::Update(double elapsed)
{
    mP = mP + mV * elapsed;
}

/**
 * Draw the item
 * @param graphics context
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    gc->DrawBitmap(*mItemBitmap,
        GetX() - GetWidth() / 2.0,
        GetY() - GetHeight() / 2.0,
        GetWidth(),
        GetHeight());
}

/**
 * Checks collision between two items
 * @param item item colliding with
 * @return collision bool
 */
bool Item::CollisionTest(Item * item)
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetWidth() / 2;
    auto itemRight = item->GetX() + item->GetWidth() / 2;
    auto itemTop = item->GetY() - item->GetHeight() / 2;
    auto itemBottom = item->GetY() + item->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all non-collision cases
    if (ourRight < itemLeft ||  // Completely to the left
        ourLeft > itemRight ||  // Completely to the right
        ourTop > itemBottom ||  // Completely below
        ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}