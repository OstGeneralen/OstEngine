// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include "Game/Actor.h"
#include "Game/Component.h"
#include "Game/Components/CameraComponent.h"
#include "Game/Components/StaticMeshComponent.h"
#include "Game/GameInterface.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

OstEngine::OstEngine()
{
}

OstEngine::~OstEngine()
{
}

void OstEngine::Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager)
{
    _gfxAssetManager.SetResourceManager(gfxResourceManager);

    _gameInstance = std::move(gameInstance);
    _gameInstance->Load(*this);
}

void OstEngine::Tick()
{
    _timer.Tick();
    _timeData.clampedDeltaTime = _timer.GetRestrictedDeltaTime(1.0f);
    _timeData.deltaTime = _timer.GetDeltaTime();
    _timeData.totalTime = _timer.GetTotalTime();

    _gameInstance->Update(*this);
    _scene.Tick(*this);

    _input.EndFrame();
}

void OstEngine::RenderScene(IRenderer& renderer)
{
    const CameraComponent* cameraComponent = nullptr;
    for (auto& actor : _scene.GetActors())
    {
        if (const CameraComponent* cameraComp = actor->GetComponent<CameraComponent>())
        {
            cameraComponent = cameraComp;
        }

        if (const StaticMeshComponent* staticMeshComp = actor->GetComponent<StaticMeshComponent>())
        {
            renderer.PushRenderCommand(staticMeshComp->GetModel(), actor->GetTransform().GetWorldTransform());
        }
    }

    renderer.ExecuteRenderCommands(cameraComponent->GetViewMatrix(renderer.GetRenderDimensions()));
}

InputReader& OstEngine::GetInputReader()
{
    return _input;
}

// ------------------------------------------------------------
// Engine Context

GraphicsAssetsManager& OstEngine::GetAssetManager()
{
    return _gfxAssetManager;
}

const TimeStructure& ost::OstEngine::GetTime() const
{
    return _timeData;
}

Scene& OstEngine::GetScene()
{
    return _scene;
}

const InputReader& OstEngine::GetInput() const
{
    return _input;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------