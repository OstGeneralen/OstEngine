#include "AppBase.h"

// ------------------------------------------------------------

void ost::COstEngineApp::Init()
{
    _appWindow = new CWindow( WindowTitle().c_str(), WindowDimensions() );
}

// ------------------------------------------------------------

void ost::COstEngineApp::DeInit()
{
    if (_appWindow)
    {
        delete _appWindow;
        _appWindow = nullptr;
    }
}

// ------------------------------------------------------------

void ost::COstEngineApp::Run()
{
    while (_appWindow && _appWindow->IsOpen())
    {
        _appWindow->RunEventLoop();

        // Begin Frame

        // End Frame
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------