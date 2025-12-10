#include "AppBase.h"
#include <OstEngine/Engine.h>

// ------------------------------------------------------------

void ost::COstEngineApp::Init()
{
    _appWindow = new CWindow( WindowTitle().c_str(), WindowDimensions() );
    
    // Create the engine instance
    CEngine::_instancePtr = new CEngine();
}

// ------------------------------------------------------------

void ost::COstEngineApp::DeInit()
{
    if (_appWindow)
    {
        delete _appWindow;
        _appWindow = nullptr;
    }

    // Destroy the engine instance
    delete CEngine::_instancePtr;
    CEngine::_instancePtr = nullptr;
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