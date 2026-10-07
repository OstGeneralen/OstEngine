// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Application.h"

#include <Engine/Game/Actor.h>
#include <Engine/Game/Components/CameraComponent.h>
#include <Engine/Game/Components/StaticMeshComponent.h>
#include <Engine/Game/GameInterface.h>
#include <Utility/Timer.h>

using namespace ost;

// ------------------------------------------------------------

LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

// ------------------------------------------------------------

void Application::Startup()
{
    _window = platform::NewWindow(*this, "Ost Application", {1600, 900}, false);

    // Create gfx settings and init graphics engine
    _graphicsEngineSettings.output.clientSize = platform::GetClientSize(_window);
    _graphicsEngineSettings.output.renderSize = {1.0f, 1.0f};
    _graphicsEngineSettings.output.nativeWindowHandle = _window;

    _graphicsEngineSettings.renderer.clearColor = Colors::Black;

    _graphicsEngine.Initialize(_graphicsEngineSettings);
    _coreEngine.GetAssetManager().SetResourceManager(_graphicsEngine.GetResourceManager());
}

void ost::Application::Shutdown()
{
    _graphicsEngine.Shutdown();
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
    const Vector2u oldSize = _graphicsEngineSettings.output.clientSize;
    const Vector2u newSize = platform::GetClientSize(_window);

    if (oldSize != newSize)
    {
        _graphicsEngineSettings.output.clientSize = newSize;
        _graphicsEngine.UpdateSettings(_graphicsEngineSettings);
    }
}

void ost::Application::Run()
{
    Timer appTimer;

    auto gamePtr = CreateGameInstance();
    _coreEngine.AssignToGameInstance(*gamePtr);
    _coreEngine.GetAssetManager().SetResourceManager(_graphicsEngine.GetResourceManager());

    gamePtr->Load();

    while (!_hasExitRequest)
    {
        appTimer.Tick();

        platform::WindowUpdate(_window);

        gamePtr->Update(appTimer.GetDeltaTime());

        // Build the scene graph
        auto& scene = _coreEngine.GetScene();

        Matrix4x4 cameraMatrix;

        scene.Update(appTimer.GetDeltaTime());

        for (auto& actor : scene.GetActors())
        {
            if (const StaticMeshComponent* meshComponent = actor->GetComponent<StaticMeshComponent>())
            {
                _graphicsEngine.PushRenderCommand(meshComponent->GetModel(), actor->GetTransform().GetWorldTransform());
            }

            if (const CameraComponent* camera = actor->GetComponent<CameraComponent>())
            {
                cameraMatrix = actor->GetTransform().GetWorldTransform().GetInverse() * camera->GetProjectionMatrix();
            }
        }

        _graphicsEngine.ExecuteRenderCommands(cameraMatrix);
        _graphicsEngine.ClearRenderCommands();
    }

    gamePtr->Unload();
    gamePtr = nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------