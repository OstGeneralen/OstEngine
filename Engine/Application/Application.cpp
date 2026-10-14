// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Application.h"

#include "CoutLogSink.h"

#include <OstLog.h>

#include <Engine/Configuration/RuntimeConfig.h>
#include <Engine/Game/GameInterface.h>
#include <Utility/Timer.h>

using namespace ost;

// ------------------------------------------------------------

void Application::Startup()
{
    Log::RegisterLogSink(Ptr::NewUnique<CoutLogSink>());

    RuntimeConfig config;
    config.LoadFromFile("Configuration.json");

    _window = platform::NewWindow(*this, config.window.title, config.window.resolution, config.window.fullscreen);

    // Create gfx settings and init graphics engine
    _graphicsEngineSettings.output.clientSize = platform::GetClientSize(_window);
    _graphicsEngineSettings.output.renderSize = config.rendering.renderScale;
    _graphicsEngineSettings.output.nativeWindowHandle = _window;
    _graphicsEngineSettings.output.fullscreen = config.window.fullscreen;

    _graphicsEngineSettings.renderer.rendererType = config.rendering.renderer;
    _graphicsEngineSettings.renderer.clearColor = Colors::Black;

    _graphicsEngine = IGraphicsEngine::CreateNew(_graphicsEngineSettings);

    OstEngineSettings coreEngineSettings;
    coreEngineSettings.pGfxEngine = _graphicsEngine.Get();
    coreEngineSettings.assetsCfg = config.assets;

    _coreEngine = IOstEngine::CreateNew(CreateGameInstance(), coreEngineSettings);
}

void ost::Application::Shutdown()
{
    _graphicsEngine = nullptr;
    _coreEngine = nullptr;
    platform::CloseWindow(_window);
}

void ost::Application::RequestExit()
{
    _hasExitRequest = true;
}

void ost::Application::BeginWindowResize()
{
}

void ost::Application::ExitWindowResize()
{
    if (!_graphicsEngine)
    {
        return;
    }

    const Vector2u oldSize = _graphicsEngineSettings.output.clientSize;
    const Vector2u newSize = platform::GetClientSize(_window);

    if (oldSize != newSize)
    {
        _graphicsEngineSettings.output.clientSize = newSize;
        _graphicsEngine->UpdateSettings(_graphicsEngineSettings);
    }
}

void ost::Application::ProcessKeyEvent(EKeyboard key, bool state)
{
    _coreEngine->GetInputReader().ProcessKeyEvent(key, state);
}

void ost::Application::Run()
{
    while (!_hasExitRequest)
    {
        platform::WindowUpdate(_window);
        _coreEngine->Tick();
        _coreEngine->RenderSceneGraph(_graphicsEngine->GetRenderQueue(), _graphicsEngine->GetRenderer());
        _graphicsEngine->ExecuteAndClearCommandQueue();
    }

    // gamePtr->Unload();
    // gamePtr = nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------