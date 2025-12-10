#include "AppBase.h"
#include <OstEngine/Engine.h>

// ------------------------------------------------------------

void ost::COstEngineApp::Init()
{
    Init_PreEngine();

    _appWindow = new CWindow( WindowTitle().c_str(), WindowDimensions() );
    // Create the engine instance
    CEngine::_instancePtr = new CEngine();

    Init_PostEngine( *CEngine::Instance() )
}

// ------------------------------------------------------------

void ost::COstEngineApp::DeInit()
{
    DeInit_PreEngine( *CEngine::Instance() );

    if (_appWindow)
    {
        delete _appWindow;
        _appWindow = nullptr;
    }

    // Destroy the engine instance
    delete CEngine::_instancePtr;
    CEngine::_instancePtr = nullptr;

    DeInit_PostEngine();
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