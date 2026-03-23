/**
 * @file ScoreBoard.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "ScoreBoard.h"

#include <wx/graphics.h>
#include <wx/font.h>
#include <sstream>
#include <iomanip>

///Font size
const int ScoreFontSize = 48;

///Score Padding
const double ScorePadding = 20.0;

///Score Padding Right
const double ScorePaddingRight = 80.0;

///Score Y pos
const double ScoreY = 10.0;

/**
 * Constructor
 * @param width The virtual pixel width of the playing area
 */
ScoreBoard::ScoreBoard(double width) : mWidth(width)
{
}

/**
 * Update the scoreboard by advancing elapsed time.
 * @param elapsed Seconds since last frame
 */
void ScoreBoard::Update(double elapsed)
{
    mElapsedTime += elapsed;
}

/**
 * Draw the scoreboard on screen.
 *
 * Timer is displayed as M:SS on the upper left.
 * Score is displayed as an integer on the upper right.
 *
 * @param graphics The graphics context to draw on
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    int totalSeconds = static_cast<int>(mElapsedTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream timerStream;
    timerStream << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    std::string timerStr = timerStream.str();
    std::string scoreStr = std::to_string(mScore);
    wxFont font(wxSize(0, ScoreFontSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);

    /// Draw timer with shadow
    graphics->SetFont(font, *wxBLACK);
    graphics->DrawText(timerStr, ScorePadding + 2, ScoreY + 2);

    graphics->SetFont(font, *wxWHITE);
    graphics->DrawText(timerStr, ScorePadding, ScoreY);

    /// Measure score text width so it can be right-ali8gned
    double textWidth, textHeight;
    graphics->GetTextExtent(scoreStr, &textWidth, &textHeight);

    double scoreX = mWidth - ScorePaddingRight - textWidth;

    /// Draw score with shadow
    graphics->SetFont(font, *wxBLACK);
    graphics->DrawText(scoreStr, scoreX + 2, ScoreY + 2);

    graphics->SetFont(font, *wxWHITE);
    graphics->DrawText(scoreStr, scoreX, ScoreY);
}

/**
 * Add points to the current score.
 * @param points Number of points to add
 */
void ScoreBoard::AddScore(int points)
{
    mScore += points;
}

/**
 * Double the current score (power-up effect).
 */
void ScoreBoard::DoubleScore()
{
    mScore *= 2;
}

/**
 * Reset the scoreboard for a new level.
 */
void ScoreBoard::Reset()
{
    mElapsedTime = 0.0;
    mScore = 0;
}