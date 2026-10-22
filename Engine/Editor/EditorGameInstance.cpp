// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorGameInstance.h"

#include "EditorContext.h"

// World
#include <Engine/World/Actor.h>
#include <Engine/World/ISceneManager.h>
#include <Engine/World/Scene.h>

// Components
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/DirectionalLightComponent.h>
#include <Engine/Components/StaticMeshComponent.h>

// ------------------------------------------------------------

ost::Actor* camera;

void ost::EditorGameInstance::Load(IAssetManager& assets)
{
    ost::HMaterial materialRoot = assets.Load<ost::IMaterial>("Engine/Materials/Mat_DefaultLit.json");
    ost::HMaterialInstance leatherMaterial = assets.Load<ost::IMaterialInstance>("Assets/Materials/LeatherMaterial.json");
    ost::HModel cubeModel = assets.Load<ost::HModel>("Assets/Models/TestCube.fbx");

    auto& sceneManager = ost::pEngine->GetServiceLocator().GetRequired<ost::ISceneManager>();

    ost::Scene* scene = sceneManager.CreateScene();

    camera = scene->CreateActor();
    camera->SetName("Camera");
    auto& cameraComponent = camera->AddComponent<ost::CameraComponent>();
    cameraComponent.MakePerspective(90.0f * ost::math::DegToRad);
    camera->transform.Move({0, 0, -5});

    ost::Actor* cube = scene->CreateActor();
    cube->SetName("Cube");
    auto& meshComponent = cube->AddComponent<ost::StaticMeshComponent>();
    meshComponent.SetModel(cubeModel);
    meshComponent.SetMaterial(leatherMaterial);
    cube->transform.Rotate(ost::Quaternion::FromEulers(45.0f * ost::math::DegToRad, 45.0f * ost::math::DegToRad, 0));

    ost::Actor* sun = scene->CreateActor();
    sun->SetName("Sun");
    auto& dirLight = sun->AddComponent<ost::DirectionalLightComponent>();
    dirLight.SetColor(ost::Colors::White);
    dirLight.SetIntensity(2.0f);
    sun->transform.SetRotation(ost::Quaternion::FromEulers(80.0f * ost::math::DegToRad, 0, 0));

    sceneManager.SetActiveScene(scene);
}

void ost::EditorGameInstance::Unload(IAssetManager& assets)
{
}

void ost::EditorGameInstance::Update(Float32 deltaTime)
{
    camera->transform.Move({0, 0, 1});
    camera->transform.Move({0, 0, -1});
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------