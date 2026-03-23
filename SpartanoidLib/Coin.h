/**
* @file Coin.h
 * @author Kyle Nguyen
 *
 * Coin item that has a 20% chance of spawning when a brick is hit.
 * Animates with a spinning effect, is affected by gravity, and
 * bounces off left/right walls.
 */

#ifndef PROJECT1_COIN_H
#define PROJECT1_COIN_H

#include "Item.h"
#include <vector>
#include <memory>
#include <wx/bitmap.h>

/**
 * Coin item class
 */
class Coin : public Item
{
private:
    /// Image frames
    std::vector<std::shared_ptr<wxBitmap>> mFrames;

    /// Images
    std::vector<std::shared_ptr<wxImage>> mImages;

    /// Current frame
    int mCurrentFrame = 0;

    /// Frame time
    double mFrameTime = 0.0;

    /// Frame duration
    static constexpr double FrameDuration = 0.08;

    /// Gravity
    static constexpr double Gravity = 500.0;

    /// Value
    int mValue = 50;

public:
    /**
     * Constructor
     * @param game The Spartanoid game this coin belongs to
     * @param baseImage Base filename for the animation frames
     * @param frames Number of animation frames
     * @param value Score value of the coin
     */
    Coin(Spartanoid* game,
         const std::wstring& baseImage,
         int frames,
         int value);

    /**
     * Update the coin animation and movement.
     * @param elapsed Time since the last update in seconds
     */
    void Update(double elapsed) override;

    /**
     * Draw the current animation frame of the coin.
     * @param gc Graphics context used for drawing
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    /**
     * returns value of coin
     * @return value of coin
     */
    int GetValue() const { return mValue; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitCoin(this); }
};

#endif // PROJECT1_COIN_H