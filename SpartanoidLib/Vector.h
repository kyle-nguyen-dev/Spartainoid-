/**
* @file Vector.h
 * @author Anik Momtaz
 *
 * 2D vector class
 */

#ifndef _VECTOR_H
#define _VECTOR_H

/**
 * 2D vector class
 *
 * This class implements vector operations and operator overloading
 * to simplify the use of 2d vectors in a C++ program.
 */
class Vector
{
public:
    /**
     * Constructor
     * @param x Initial X value
     * @param y Initial Y value
     */
    Vector(double x, double y);

    /**
     * Default constructor (initializes to 0,0)
     */
    Vector();

    /**
     * Destructor
     */
    virtual ~Vector() = default;

    /**
     * Multiply vector by scalar.
     * @param d Scalar value
     * @return Resulting vector
     */
    Vector operator*(double d) const;

    /**
     * Add another vector to this one.
     * @param a Vector to add
     * @return Reference to this vector
     */
    Vector & operator+=(const Vector & a);

    /**
     * Multiply this vector by a scalar.
     * @param d Scalar value
     * @return Reference to this vector
     */
    Vector & operator*=(double d);

    /**
     * Divide this vector by a scalar.
     * @param d Scalar value
     * @return Reference to this vector
     */
    Vector & operator/=(double d);

    /**
     * Assignment operator.
     * @param a Value to assign to this object
     * @return (*this)
     */
    Vector& operator=(const Vector& a) = default;

    /// Get the X value
    /// @return X
    [[nodiscard]] auto X() const { return mX; }

    /// Get the Y value
    /// @return Y
    [[nodiscard]] auto Y() const { return mY; }

    /// Set the vector
    /// @param x X value
    /// @param y Y value
    void Set(double x, double y) { mX = x; mY = y; }

    /// Set the vector from another vector
    /// @param x Other vector
    void Set(const Vector &x) { mX = x.mX; mY = x.mY; }

    /// Set the X component of the vector
    /// @param x X value
    void SetX(double x) { mX = x; }

    /// Set the Y component of the vector
    /// @param y Y value
    void SetY(double y) { mY = y; }

    /**
     * Compute the length (magnitude) of the vector.
     * @return Length of the vector
     */
    [[nodiscard]] double Length() const;

    /**
     * Compute distance to another vector.
     * @param other The other vector
     * @return Distance between the two vectors
     */

    [[nodiscard]] double Distance(const Vector & other) const;

    /**
     * Normalize the vector (make it unit length).
     * @return Reference to this vector
     */
    Vector & Normalize();

private:
    /// X component of vector
    double mX;

    /// Y component of vector
    double mY;
};

/**
 * Add two vectors.
 * @param a First vector
 * @param b Second vector
 * @return Resulting vector
 */
Vector operator+(const Vector & a, const Vector & b);

/**
 * Subtract two vectors.
 * @param a First vector
 * @param b Second vector
 * @return Resulting vector
 */
Vector operator-(const Vector & a, const Vector & b);

/**
 * Divide a vector by a scalar.
 * @param a Vector
 * @param d Scalar value
 * @return Resulting vector
 */
Vector operator/(const Vector & a, double d);

#endif // _VECTOR_H