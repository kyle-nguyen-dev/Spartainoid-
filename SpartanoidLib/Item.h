/**
 * @file Item.h
 * @author Sam Nowlan
 */

#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <wx/image.h>
#include <wx/bitmap.h>
#include "Vector.h"
#include "ItemVisitor.h"

class Spartanoid;
class wxGraphicsContext;
class Ball;
class Coin;

/**
 * Base Class for all game items
 */
class Item
{
public:

protected:
    Item(Spartanoid *spartanoid, const std::wstring &filename);

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;
private:
    /// spartanoid item
    Spartanoid* mSpartanoid;

    /// Position
    Vector mP;

    /// Velocity in virtual pixels/second
    Vector mV;

    /// Size of the item width
    double mWidth = 0;

    /// Height of item
    double mHeight = 0;

    /// Is the item active boolean
    bool mActive = true;

public:
    /// Virtual destructor
    virtual ~Item() {}
    
    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    /// Update the item
    virtual void Update(double elapsed);

    /// Draw the item
    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);

    /// Test collision
    virtual bool CollisionTest(Item* item);

    /**
     * Sets Position
     * @param x pos x
     * @param y pos y
     */
    void SetPosition(double x, double y) {mP = Vector(x, y);}

    /**
     * Gets pos x
     * @return pos x
     */
    double GetX() const {return mP.X();}
    /**
     * Gets pos y
     * @return pos y
     */
    double GetY() const {return mP.Y();}

    /** Get position vector @return Position vector */
    Vector GetP() const { return mP; }

    /** Set position from vector
    * @param p Position vector */
    void SetP(Vector p) { mP = p; }

    /** Get velocity @return Velocity vector */
    Vector GetV() const { return mV; }

    /** Set velocity
    * @param vx X velocity
    * @param vy Y velocity */
    void SetVelocity(double vx, double vy) { mV = Vector(vx, vy); }

    /**
     * Handles item action when screen is clicked.
     */
    virtual void OnClick(){};

    /** Set velocity from vector
    * @param v Velocity vector */
    void SetV(Vector v) { mV = v; }

    /** Get X velocity @return X velocity */
    double GetVelocityX() const { return mV.X(); }

    /** Get Y velocity @return Y velocity */
    double GetVelocityY() const { return mV.Y(); }

    /**
     * Gets Width
     * @return width of item
     */
    double GetWidth() const {return mWidth;}
    /**
     * Gets height of item
     * @return Height
     */
    double GetHeight() const {return mHeight;}

    /**
     * returns active state of item
     * @return items active state
     */
    bool IsActive() const {return mActive;}

    /**
     * Sets item active status
     * @param active item active status
     */
    void SetActive(bool active) {mActive = active;}

    /**
     * Handles item hit by ball
     * @param ball Ball hitting item
     */
    virtual void HitByBall(Ball* ball) {}

    /**
     * Handles item hit by coin
     * @param coin Coin hitting item
     */
    virtual void HitByCoin(Coin* coin) {}

    /**
     * return game
     * @return main game object
     */
    Spartanoid* GetSpartanoid() const {return mSpartanoid;}

    /**
     * Accepts visitor to objects
     * @param visitor visitor accepted to object
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * Sets the size of item
     * @param w width
     * @param h height
     */
    void SetSize(double w, double h)
    {
        mWidth = w;
        mHeight = h;
    }
};

#endif //ITEM_H