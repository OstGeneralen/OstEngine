// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

// Game World
#include <Engine/World/Actor.h>
#include <Engine/World/ISceneManager.h>
#include <Engine/World/Scene.h>

// Engine Resources
#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>

// Engine Components
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/DirectionalLightComponent.h>
#include <Engine/Components/StaticMeshComponent.h>

// ------------------------------------------------------------

ost::UniquePtr<ost::GameBase> ost::CreateGameInstance()
{
    return ost::Ptr::NewUnique<Game>();
}

// ------------------------------------------------------------

void Game::Load(ost::IAssetManager& assets)
{
    ost::HMaterial materialRoot = assets.Load<ost::IMaterial>("Engine/Materials/Mat_DefaultLit.json");
    ost::HMaterialInstance leatherMaterial = assets.Load<ost::IMaterialInstance>("Assets/Materials/LeatherMaterial.json");
    ost::HModel cubeModel = assets.Load<ost::HModel>("Assets/Models/TestCube.fbx");

    auto& sceneManager = ost::pEngine->GetServiceLocator().GetRequired<ost::ISceneManager>();

    ost::Scene* scene = sceneManager.CreateScene();

    ost::Actor* camera = scene->CreateActor();
    camera->AddComponent<KeyboardMovementComponent>();
    auto& cameraComponent = camera->AddComponent<ost::CameraComponent>();
    cameraComponent.MakePerspective(90.0f * ost::math::DegToRad);
    camera->transform.Move({0, 0, -5});

    ost::Actor* cube = scene->CreateActor();
    auto& meshComponent = cube->AddComponent<ost::StaticMeshComponent>();
    meshComponent.SetModel(cubeModel);
    meshComponent.SetMaterial(leatherMaterial);
    cube->transform.Rotate(ost::Quaternion::FromEulers(45.0f * ost::math::DegToRad, 45.0f * ost::math::DegToRad, 0));

    ost::Actor* sun = scene->CreateActor();
    auto& dirLight = sun->AddComponent<ost::DirectionalLightComponent>();
    dirLight.SetColor(ost::Colors::White);
    dirLight.SetIntensity(2.0f);
    sun->transform.SetRotation(ost::Quaternion::FromEulers(80.0f * ost::math::DegToRad, 0, 0));

    sceneManager.SetActiveScene(scene);
}

void Game::Unload(ost::IAssetManager& context)
{
}

void Game::Update(Float32 deltaTime)
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------