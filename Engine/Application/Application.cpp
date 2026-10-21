// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Application.h"

#include "CoutLogSink.h"

#include <OstLog.h>

#include <Engine/Configuration/RuntimeConfig.h>
#include <Engine/Game/GameBase.h>
#include <Utility/Timer.h>

using namespace ost;

// ------------------------------------------------------------

void Application::Startup()
{
    // Initialize Logger Subsystem
    Log::RegisterLogSink(Ptr::NewUnique<CoutLogSink>());

    // Load the config and create window from it
    RuntimeConfig config;
    config.LoadFromFile("Configuration.json");
    _window.Create(*this, config.window.title, config.window.resolution, config.window.fullscreen);

    // Build Core Engine + Graphics Engine
    _coreEngine = IOstEngine::Create(_serviceLocator);
    _graphicsEngine = IGraphicsEngine::Create(_serviceLocator, _window.GetNativeWindowHandle(), _window.GetClientSize());
    _gameInstance = CreateGameInstance();

    _coreEngine->SetGameInstance(_gameInstance.Get());

}

void ost::Application::Shutdown()
{
    _graphicsEngine = nullptr;
    _coreEngine = nullptr;
    _window.Close();
}

void ost::Application::RequestExit()
{
    _hasExitRequest = true;
}

void ost::Application::Resized()
{
    if (!_graphicsEngine)
    {
        return;
    }

    const Vector2u newSize = _window.GetClientSize();
    _graphicsEngine->SetOutputSize(newSize);
    _graphicsEngine->SetRenderSize(newSize);
}

void ost::Application::ProcessKeyEvent(EKeyboard key, bool state)
{
    _coreEngine->GetInputReader().ProcessKeyEvent(key, state);
}

void ost::Application::Run()
{
    while (!_hasExitRequest)
    {
        _window.Update();
        _coreEngine->Tick();
        _coreEngine->RenderSceneGraph(_graphicsEngine->GetRenderQueue(), _graphicsEngine->GetRenderer());
        _graphicsEngine->ExecuteAndClearCommandQueue();
        _graphicsEngine->ClearAndSetBackbuffer();
        _graphicsEngine->DrawRendererOutput();
        _graphicsEngine->Present();
    }

    // gamePtr->Unload();
    // gamePtr = nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------