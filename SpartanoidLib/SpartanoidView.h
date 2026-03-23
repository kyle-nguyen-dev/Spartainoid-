/**
 * @file SpartanoidView.h
 * @author Nick Tokarz
 * @author Sam Nowlan
 *
 * View class for the Spartanoid game.
 */

#ifndef PROJECT1_SPARTANOIDVIEW_H
#define PROJECT1_SPARTANOIDVIEW_H

#include <memory>
#include <wx/timer.h>
#include <wx/stopwatch.h>
#include "Spartanoid.h"

/**
 * View class for spartanoid game
 */
class SpartanoidView : public wxWindow
{
private:
    /// An object that describes our spartanoid
    std::shared_ptr<Spartanoid> mSpartanoid;

    /// The timer that allows for animation
    wxTimer mTimer;

    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnLeftDown(wxMouseEvent& event);

    void OnLoadLevel0(wxCommandEvent& event);
    void OnLoadLevel1(wxCommandEvent& event);
    void OnLoadLevel2(wxCommandEvent& event);
    void OnLoadLevel3(wxCommandEvent& event);

    void OnPaddleDefault(wxCommandEvent& event);
    void OnPaddleX15(wxCommandEvent& event);
    void OnPaddleX2(wxCommandEvent& event);

    /// Defines if paddle is moving left
    bool mMoveLeft = false;

    /// Defines if paddle is moving right
    bool mMoveRight = false;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// Time of the last update
    long mLastTime = 0;      

public:
    void Initialize(wxFrame* parent);
};

#endif //PROJECT1_SPARTANOIDVIEW_H