/**
 * @file MainFrame.cpp
 * @author Nick Tokarz
 * @author Sam Nowlan
 */

#include "pch.h"
#include "MainFrame.h"

#include "ids.h"
#include "SpartanoidView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Spartanoid",
           wxDefaultPosition,  wxSize(1150, 800));


    // Sizer to lay out child windows vertically
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto spartanoidView = new SpartanoidView();
    spartanoidView->Initialize(this);

    // Add it to the sizer
    sizer->Add(spartanoidView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    // Create the menu bar and menus
    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto paddleMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(paddleMenu, L"&Paddle Difficulty");
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Load level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Load level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Load level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Load level 3");

    paddleMenu->Append(IDM_PADDLE_DEFAULT, L"&Default", L"Set paddle speed to default");
    paddleMenu->Append(IDM_PADDLE_X15, L"&x1.5", L"Set paddle speed to 1.5x");
    paddleMenu->Append(IDM_PADDLE_X2, L"&x2", L"Set paddle speed to 2x");

    SetMenuBar( menuBar );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Spartanoid!",
            L"About Spartanoid",
            wxOK,
            this);
}