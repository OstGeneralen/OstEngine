// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include <Engine/Asset/GraphicsAssetsManager.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/SceneLightComponent.h>
#include <Engine/Components/StaticMeshComponent.h>
#include <Engine/EngineContext.h>
#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

#include "KeyboardMovementComponent.h"

// ------------------------------------------------------------

ost::UniquePtr<ost::IGame> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

void Game::Load(ost::EngineContext& context)
{
    _scene = context.CreateScene(true);

    ost::Actor* meshActor = _scene->CreateActor();
    meshActor->AddComponent<ost::StaticMeshComponent>(context.AssetManager().LoadModel("Meshes/MultiMeshModel.fbx"));

    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(90.0f * (3.141f / 180.0f));
    cameraActor->transform.Move({0.0f, 0.0f, -10.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    ost::Vector3f sunDir = {0.5f, -1.0f, 0.0f};
    sunDir.Normalize();

    ost::Actor* lightActor = _scene->CreateActor();
    auto& sceneLight = lightActor->AddComponent<ost::SceneLightComponent>();
    sceneLight.SetSunDirection( sunDir );
}

void Game::Unload(ost::EngineContext& context)
{
}

void Game::Update(ost::EngineContext& context)
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------