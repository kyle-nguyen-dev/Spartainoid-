/**
 * @file ScoreBoard.h
 * @author Kyle Nguyen
 *
 *
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H

#include <memory>

class wxGraphicsContext;

/**
 * Manages and displays the game scoreboard.
 *
 * Tracks elapsed time (displayed as M:SS on the left)
 * and the current score (displayed on the right).
 * The scoreboard is drawn on top of all other content.
 */
class ScoreBoard
{
private:
    /// Elapsed time in seconds since the level started
    double mElapsedTime = 0.0;

    /// Current score for this level
    int mScore = 0;

    /// Width of the display area in virtual pixels
    double mWidth = 1024;

public:
    /**
     * Constructor
     * @param width The virtual pixel width of the playing area
     */
    ScoreBoard(double width = 1024);

    /**
     * Update the scoreboard by advancing the timer.
     * @param elapsed Seconds since last frame
     */
    void Update(double elapsed);

    /**
     * Draw the scoreboard (timer left, score right) on top of all content.
     * @param graphics The graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /** Set the width of the playing area
    * @param width Width in virtual pixels */
    void SetWidth(double width) { mWidth = width; }

    /**
     * Add points to the current score.
     * @param points Number of points to add
     */
    void AddScore(int points);

    /**
     * Double the current score (power-up effect).
     */
    void DoubleScore();

    /**
     * Reset the scoreboard (timer and score) for a new level.
     */
    void Reset();

    /**
     * Get the current score.
     * @return Current score
     */
    int GetScore() const { return mScore; }

    /**
     * Get elapsed time in seconds.
     * @return Elapsed time
     */
    double GetElapsedTime() const { return mElapsedTime; }
};

#endif //PROJECT1_SCOREBOARD_H