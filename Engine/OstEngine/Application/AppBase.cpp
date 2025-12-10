#include "AppBase.h"
#include <OstEngine/Engine.h>

// ------------------------------------------------------------

void ost::COstEngineApp::Init()
{
    Init_PreEngine();

    _appWindow = new CWindow( WindowTitle().c_str(), WindowDimensions() );
    // Create the engine instance
    CEngine::_instancePtr = new CEngine();

    CEngine& engine = *CEngine::Instance();
    engine.InitializeRendering( *_appWindow );
    Init_PostEngine( engine );
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

    CEngine::Instance()->Deinitialize();

    // Destroy the engine instance
    delete CEngine::_instancePtr;
    CEngine::_instancePtr = nullptr;

    DeInit_PostEngine();
}

// ------------------------------------------------------------

void ost::COstEngineApp::Run()
{
    CEngine& engine = *CEngine::Instance();
    SColor clearColor = 0x121212FF;

    while (_appWindow && _appWindow->IsOpen())
    {
        // Frame Start
        _appWindow->RunEventLoop();
        engine.GetRenderer().BeginFrame( clearColor );

        Tick();

        // Frame End
        engine.GetRenderer().EndFrame();
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------