/**
 * @file Level.h
 * @author Omar Martinez
 * @author Sam Nowlan
 *
 * Class that represents game level
 */

#pragma once

#include <memory>
#include <vector>
#include <wx/xml/xml.h>
#include <wx/image.h>

class Spartanoid;
class Item;
class Paddle;
class Brick;
class Enemy;
class wxGraphicsContext;

/**
 * Class that represents a game level
 */
class Level
{
private:
    /// The XML document for this level
    wxXmlDocument mXmlDoc;

    /// The width of the level in virtual pixels
    int mWidth = 0;

    /// The height of the level in virtual pixels
    int mHeight = 0;

    /// Coin image
    std::wstring mCoinImage;

    /// Coin frames
    int mCoinFrames = 0;

    /// Coin score value
    int mCoinValue = 0;

    /// Level has coin
    bool mHasCoin = false;

public:
    /**
     * Constructor
     * @param levelNumber The level number to load
     */
    Level(int levelNumber);

    /**
     * Populate the item list for this level.
     * @param game The Spartanoid game this level belongs to
     * @param items The item list to populate
     * @param paddle The paddle pointer to initialize
     */
    void PopulateItems(Spartanoid* game,
                       std::vector<std::shared_ptr<Item>>& items,
                       std::shared_ptr<Paddle>& paddle);

    /** Get the level width
    * @return Level width in virtual pixels */
    int GetWidth() const { return mWidth; }

    /** Get the level height
     * @return Level height in virtual pixels */
    int GetHeight() const { return mHeight; }
    /**
     * Returns if there are coins in the level
     * @return Has coin bool
     */
    bool HasCoin() const { return mHasCoin; }

    /**
     * returns the coin image
     * @return coin image
     */
    std::wstring GetCoinImage() const { return mCoinImage; }

    /**
     * returns coin frames
     * @return coin frames
     */
    int GetCoinFrames() const { return mCoinFrames; }

    /**
     * returns the coin value
     * @return coin value
     */
    int GetCoinValue() const { return mCoinValue; }
};