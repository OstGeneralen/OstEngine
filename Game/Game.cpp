// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

#include <Engine/Asset/IAssetManager.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/DirectionalLightComponent.h>
#include <Engine/Components/SceneLightComponent.h>
#include <Engine/Components/StaticMeshComponent.h>
#include <Engine/EngineContext.h>
#include <Engine/Game/GameContext.h>
#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

// ------------------------------------------------------------

ost::UniquePtr<ost::IGame> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

ost::Actor* pLightActor = nullptr;

// ------------------------------------------------------------

void Game::Load(ost::GameContext& context)
{
    _scene = context.CreateScene(true);

    auto& assets = ost::EngineContext::Get().Assets();

    ost::HModel cubeModel = assets.Load<ost::HModel>("Game/TestCube");
    ost::HModel planeModel = assets.Load<ost::HModel>("Game/TestPlane");

    // Now create the material instance we'll use
    assets.Load<ost::IMaterialInstance>("Game/RockMaterial");
    assets.Load<ost::IMaterialInstance>("Game/LeatherMaterial");
    assets.Load<ost::IMaterialInstance>("Game/MossMaterial");
    assets.Load<ost::IMaterialInstance>("Game/MetalMaterial");

    // Now let's create the plane actor
    ost::Actor* leftActor = _scene->CreateActor();
    auto& leftMeshComponent = leftActor->AddComponent<ost::StaticMeshComponent>();
    leftActor->transform.SetPosition({-2.5f, 0, 0});
    //leftActor->AddComponent<KeyboardRotatorComponent>();

    ost::Actor* centerActor = _scene->CreateActor();
    auto& centerMeshComponent = centerActor->AddComponent<ost::StaticMeshComponent>();
    //centerActor->AddComponent<KeyboardRotatorComponent>();

    ost::Actor* rightActor = _scene->CreateActor();
    auto& rightMeshComponent = rightActor->AddComponent<ost::StaticMeshComponent>();
    rightActor->transform.SetPosition({2.5f, 0, 0});
    //rightActor->AddComponent<KeyboardRotatorComponent>();

    leftMeshComponent.SetModel(cubeModel);
    leftMeshComponent.SetMaterial("Game/MetalMaterial");

    rightMeshComponent.SetModel(cubeModel);
    rightMeshComponent.SetMaterial("Game/LeatherMaterial");

    centerMeshComponent.SetModel(cubeModel);
    centerMeshComponent.SetMaterial("Game/MossMaterial");

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 0.0f, -4.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    pLightActor = _scene->CreateActor();
    auto& sceneLight = pLightActor->AddComponent<ost::SceneLightComponent>();
    sceneLight.SetAmbientColor({0.0f, 0.01f, 0.02f, 1.0f});
    auto& directionalLight = pLightActor->AddComponent<ost::DirectionalLightComponent>();
    directionalLight.SetColor(ost::Color(1.0f, 0.9f, 0.7f, 1.0f), 2.0f);
    pLightActor->transform.Rotate(ost::Quaternion::FromRotationAxis(pLightActor->transform.GetRight(), 90.0f * ost::math::DegToRad));
    pLightActor->AddComponent<KeyboardRotatorComponent>();
}

void Game::Unload(ost::GameContext& context)
{
}

void Game::Update(ost::GameContext& context)
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------