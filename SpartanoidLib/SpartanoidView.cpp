/**
 * @file SpartanoidView.cpp
 * @author Nick Tokarz
 */

#include "pch.h"
#include "SpartanoidView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "ids.h"

/**
 * Initialize the spartanoid view class.
 * @param parent The parent window for this class
 */
void SpartanoidView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);

    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mSpartanoid = std::make_shared<Spartanoid>();

    mTimer.SetOwner(this);
    mTimer.Start(16);

    Bind(wxEVT_PAINT, &SpartanoidView::OnPaint, this);
    Bind(wxEVT_TIMER, &SpartanoidView::OnTimer, this);
    Bind(wxEVT_KEY_DOWN, &SpartanoidView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &SpartanoidView::OnKeyUp, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanoidView::OnLeftDown, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnLoadLevel0, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnLoadLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnLoadLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnLoadLevel3, this, IDM_LEVEL3);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnPaddleDefault, this, IDM_PADDLE_DEFAULT);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnPaddleX15, this, IDM_PADDLE_X15);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanoidView::OnPaddleX2, this, IDM_PADDLE_X2);

    SetFocus();

    mStopWatch.Start();
    mLastTime = 0;
}
/**
 * Refreshes spartanoid view on timer event
 * @param event Timer Event
 */
void SpartanoidView::OnTimer(wxTimerEvent& event)
{
    if(mMoveLeft)
        mSpartanoid->MovePaddleLeft();
    if(mMoveRight)
        mSpartanoid->MovePaddleRight();

    long currentTime = mStopWatch.Time();
    double elapsed = (currentTime - mLastTime) / 1000.0;
    mLastTime = currentTime;

    mSpartanoid->Update(elapsed);
    Refresh();
}
/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanoidView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    mSpartanoid->Draw(graphics, size.GetWidth(), size.GetHeight());
}

/**
* Handle the key down event
* @param event
*/
void SpartanoidView::OnKeyDown(wxKeyEvent& event)
{
    if(event.GetKeyCode() == WXK_LEFT || event.GetKeyCode() == 'A')
        mMoveLeft = true;

    if(event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == 'D')
        mMoveRight = true;
}
/**
* Handle the key up event
* @param event
*/
void SpartanoidView::OnKeyUp(wxKeyEvent& event)
{
    if(event.GetKeyCode() == WXK_LEFT || event.GetKeyCode() == 'A')
        mMoveLeft = false;

    if(event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == 'D')
        mMoveRight = false;
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void SpartanoidView::OnLeftDown(wxMouseEvent &event)
{
    for (auto item : mSpartanoid->GetItems())
    {
        item->OnClick();
    }
}

/**
 * Menu hander for Level>level 0
 * @param event Mouse event
 */
void SpartanoidView::OnLoadLevel0(wxCommandEvent& event)
{
    mSpartanoid->LoadLevel(0);
    Refresh();
}

/**
 * Menu hander for Level>level 1
 * @param event Mouse event
 */
void SpartanoidView::OnLoadLevel1(wxCommandEvent& event)
{
    mSpartanoid->LoadLevel(1);
    Refresh();
}

/**
 * Menu hander for Level>level 2
 * @param event Mouse event
 */
void SpartanoidView::OnLoadLevel2(wxCommandEvent& event)
{
    mSpartanoid->LoadLevel(2);
    Refresh();
}

/**
 * Menu hander for Level>level 3
 * @param event Mouse event
 */
void SpartanoidView::OnLoadLevel3(wxCommandEvent& event)
{
    mSpartanoid->LoadLevel(3);
    Refresh();
}

/**
 * Set paddle speed to default.
 * @param event Menu command event
 */
void SpartanoidView::OnPaddleDefault(wxCommandEvent& event)
{
    mSpartanoid->SetPaddleSpeedMultiplier(1.0);
}

/**
 * Set paddle speed to 1.5x.
 * @param event Menu command event
 */
void SpartanoidView::OnPaddleX15(wxCommandEvent& event)
{
    mSpartanoid->SetPaddleSpeedMultiplier(1.5);
}

/**
 * Set paddle speed to 2x.
 * @param event Menu command event
 */
void SpartanoidView::OnPaddleX2(wxCommandEvent& event)
{
    mSpartanoid->SetPaddleSpeedMultiplier(2.0);
}
