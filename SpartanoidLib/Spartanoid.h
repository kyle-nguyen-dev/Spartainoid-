/**
* @file Spartanoid.h
 * @author Sohum Jain
 * @author Sam Nowlan
 *
 * Class describes the spartanoid game
 */

#ifndef PROJECT1_SPARTANOID_H
#define PROJECT1_SPARTANOID_H

#include <memory>
#include <vector>

#include "Level.h"
#include "ScoreBoard.h"
#include "Background.h"

class Paddle;
class Ball;
class Brick;
class wxGraphicsContext;
class Level;
class Item;

/**
 * Class describes the spartanoid game
 */
class Spartanoid
{
private:
    /// The paddle object
    std::shared_ptr<Paddle> mPaddle;

    /// The items on screen
    std::vector<std::shared_ptr<Item>> mItems;

    /// Items queued to be added after the current update loop finishes
    std::vector<std::shared_ptr<Item>> mPendingItems;

    /// All levels loaded at startup
    std::vector<std::shared_ptr<Level>> mLevels;

    /// Current level number
    int mCurrentLevel = 0;

    /// width
    int mWidth = 0;

    /// height
    int mHeight = 0;

    /// virtual width
    double mVirtualWidth = 0;

    /// scoreboard
    ScoreBoard mScoreBoard;

    /// Scale of game
    double mScale = 1.0;

    /// Paddle speed multiplier
    double mPaddleSpeedMultiplier = 1.0;

    /// Lose/game-over state
    bool mGameOver = false;
    double mGameOverTime = 0.0;
    static constexpr double GameOverDelay = 2.0;

    /// Win state
    bool mGameWon = false;
    double mGameWonTime = 0.0;
    static constexpr double GameWonDelay = 2.0;

    int mStartX = 0;
    int mStartY = 0;
    int mLevel = 0;

public:
    Spartanoid();

    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    void MovePaddleLeft();
    void MovePaddleRight();

    std::shared_ptr<Paddle> GetPaddle() const { return mPaddle; }

    void LoadLevel(int levelNumber);
    void Add(std::shared_ptr<Item> item);
    void Clear();

    ScoreBoard& GetScoreBoard() { return mScoreBoard; }

    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }

    /// Game over setter
    void SetGameOver(bool gameOver) {mGameOver = gameOver;};

    /// Logic for paddle speed
    void SetPaddleSpeedMultiplier(double multiplier);

    /**
     * gets virtual width
     * @return virtual width
     */
    double GetVirtualWidth() const { return mVirtualWidth; }

    const std::vector<std::shared_ptr<Item>>& GetItems() const { return mItems; }
    std::shared_ptr<Level> GetLevel() const { return mLevels[mCurrentLevel]; }

    int GetStartX() const { return mStartX; }
    int GetStartY() const { return mStartY; }
};

#endif