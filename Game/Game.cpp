// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "InputMovementComponent.h"
#include "RotatingComponent.h"

#include <Engine/Asset/GraphicsAssetsManager.h>
#include <Engine/EngineContext.h>
#include <Engine/Game/Components/CameraComponent.h>
#include <Engine/Game/Components/StaticMeshComponent.h>
#include <Engine/Game/Scene.h>

// ------------------------------------------------------------

ost::UniquePtr<ost::IGame> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

void Game::Load(ost::EngineContext& context)
{
    auto& scene = context.GetScene();

    _meshActor = scene.NewActor();
    _meshActor->AddComponent<ost::StaticMeshComponent>(context.GetAssetManager().LoadModel("Meshes/DebugShape.fbx"));
    _meshActor->AddComponent<RotatingComponent>();

    _cameraActor = scene.NewActor();
    auto& camera = _cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(90.0f * (3.141f / 180.0f), 16.0f / 9.0f);
    _cameraActor->GetTransform().Move({0.0f, 0.0f, -10.0f}, ost::ESpace::World);
    _cameraActor->AddComponent<InputMovementComponent>();
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