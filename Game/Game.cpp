// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include <Engine/Game/Components/CameraComponent.h>
#include <Engine/Game/Components/StaticMeshComponent.h>
#include "RotatingComponent.h"
#include <Engine/OstEngine.h>

// ------------------------------------------------------------

ost::UniquePtr<ost::IGame> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

void Game::Load()
{
    auto& assetManager = GetEngine().GetAssetManager();
    auto& scene = GetEngine().GetScene();

    _meshActor = scene.NewActor();
    _meshActor->AddComponent<ost::StaticMeshComponent>(assetManager.LoadModel("Meshes/DebugShape.fbx"));
    _meshActor->AddComponent<RotatingComponent>();

    _cameraActor = scene.NewActor();
    auto& camera = _cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(90.0f * (3.141f / 180.0f), 16.0f / 9.0f);
    _cameraActor->GetTransform().Move({0.0f, 0.0f, -10.0f});
}

void Game::Unload()
{
}

void Game::Update(Float32 deltaTime)
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------