/**
* @file PowerUp.h
 * @author Kyle Nguyen
 *
 * Power-up item (Sparty). When the ball collides with it:
 *  - The current score is doubled
 *  - A second ball is spawned with mirrored velocity
 *  - The image shrinks and disappears
 *  - "Power Up!" text floats upward, grows, then disappears
 */

#ifndef PROJECT1_POWERUP_H
#define PROJECT1_POWERUP_H

#include "Item.h"
#include <string>

/**
 * Power-up item class
 */
class PowerUp : public Item
{
private:
    /// If powerup is used
    bool mConsumed = false;

    /// Time since animation started
    double mConsumedTime = 0.0;

    /// Duration for animation
    static constexpr double AnimationDuration = 1.5;

    ///Set dimensions for powerup
    double mOriginalWidth = 0;
    double mOriginalHeight = 0;

    /// Scale for shrink animation
    double mScale = 1.0;

    /// Position for text
    double mTextY = 0;

    /// Text Size
    double mTextSize = 20.0;

public:
    /**
     * Constructor
     * @param game The Spartanoid game this power-up belongs to
     * @param filename Image filename for this power-up
     */
    PowerUp(Spartanoid* game, const std::wstring& filename);

    /**
     * Update the power-up animation.
     * @param elapsed Time since the last update in seconds
     */
    void Update(double elapsed) override;

    /**
     * Draw the power-up and any active consume animation.
     * @param gc Graphics context used for drawing
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    /**
     * Handle collision with a ball.
     * @param ball The ball that hit this power-up
     */
    void HitByBall(Ball* ball) override;

    /**
     * Accept a visitor.
     * @param visitor The visitor this item accepts
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPowerUp(this); }
};

#endif // PROJECT1_POWERUP_H