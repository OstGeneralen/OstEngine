// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "KeyboardMovementComponent.h"

#include <Engine/Asset/GraphicsAssetsManager.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/SceneLightComponent.h>
#include <Engine/Components/StaticMeshComponent.h>
#include <Engine/EngineContext.h>
#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

// ------------------------------------------------------------

ost::UniquePtr<ost::IGame> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

void Game::Load(ost::EngineContext& context)
{
    _scene = context.CreateScene(true);

    // Let there be a thing
    ost::Actor* meshActor = _scene->CreateActor();
    meshActor->AddComponent<ost::StaticMeshComponent>(context.AssetManager().LoadModel("Meshes/Room.fbx"));

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 1.7f, 0.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    ost::Actor* lightActor = _scene->CreateActor();
    auto& sceneLight = lightActor->AddComponent<ost::SceneLightComponent>();
    sceneLight.SetSunDirection(ost::Vector3f(0.5f, -1.0f, 0.0f).GetNormalized());
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