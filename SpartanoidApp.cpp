/**
 * @file SpartanoidApp.cpp
 * @author Nick Tokarz
 */

#include "pch.h"
#include "SpartanoidApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool SpartanoidApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}