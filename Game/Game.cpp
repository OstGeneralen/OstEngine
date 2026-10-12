// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

#include <Engine/Asset/IAssetManager.h>
#include <Engine/Components/CameraComponent.h>
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

void Game::Load(ost::GameContext& context)
{
    _scene = context.CreateScene(true);

    auto& assets = ost::EngineContext::Get().Assets();

    ost::HModel cubeModel = assets.LoadModelFromFile("Meshes/MaterialTestPlane.fbx");
    ost::HModel planeModel = assets.LoadModelFromFile("Meshes/PlaneTest.fbx");

    // Load our two textures
    ost::HTexture rockAlbedo = assets.LoadTextureFromFile("Materials/Rock/Rock_Albedo.dds");
    ost::HTexture rockNormal = assets.LoadTextureFromFile("Materials/Rock/Rock_Normal.dds");
    ost::HTexture rockORM = assets.LoadTextureFromFile("Materials/Rock/Rock_ORM.dds");

    ost::HTexture leatherAlbedo = assets.LoadTextureFromFile("Materials/Leather/Leather_Albedo.dds");
    ost::HTexture leatherNormal = assets.LoadTextureFromFile("Materials/Leather/Leather_Normal.dds");
    ost::HTexture leatherORM = assets.LoadTextureFromFile("Materials/Leather/Leather_ORM.dds");

    // Let's create our material + instances :)
    ost::HMaterial materialHandle = assets.CreateMaterial(ost::EMaterialDomain::SurfaceLit, "MaterialShaders/ColoredSurfaceLit.hlsl");
    ost::IMaterial& material = assets.GetMaterial(materialHandle);
    material.GetPropertyDefaults().SetProperty("OverrideColor", ost::Colors::White.Vec4);
    material.GetPropertyDefaults().SetProperty("OverrideStrength", 0.0f);

    // Now create the material instance we'll use
    ost::HMaterialInstance leatherMaterial;
    leatherMaterial = assets.CreateMaterialInstance(materialHandle);
    ost::IMaterialInstance* materialInstance = &assets.GetMaterialInstance(leatherMaterial);
    materialInstance->Textures().SetTexture(ost::EMaterialTexture::Albedo, leatherAlbedo);
    materialInstance->Textures().SetTexture(ost::EMaterialTexture::Normal, leatherNormal);
    materialInstance->Textures().SetTexture(ost::EMaterialTexture::ORM, leatherORM);

    ost::HMaterialInstance rockMaterial;
    rockMaterial = assets.CreateMaterialInstance(materialHandle);
    ost::IMaterialInstance* rockMaterialInstance = &assets.GetMaterialInstance(rockMaterial);
    rockMaterialInstance->Textures().SetTexture(ost::EMaterialTexture::Albedo, rockAlbedo);
    rockMaterialInstance->Textures().SetTexture(ost::EMaterialTexture::Normal, rockNormal);
    rockMaterialInstance->Textures().SetTexture(ost::EMaterialTexture::ORM, rockORM);

    // Now let's create the plane actor
    ost::Actor* leftActor = _scene->CreateActor();
    auto& leftMeshComponent = leftActor->AddComponent<ost::StaticMeshComponent>();
    leftActor->transform.SetPosition({-1.5f, 0, 0});
    leftActor->transform.Rotate(ost::Quaternion::FromRotationAxis({1, 0, 0}, -45.0f * ost::math::DegToRad));
    leftActor->AddComponent<KeyboardRotatorComponent>();

    ost::Actor* rightActor = _scene->CreateActor();
    auto& rightMeshComponent = rightActor->AddComponent<ost::StaticMeshComponent>();
    rightActor->transform.SetPosition({1.5f, 0, 0});
    rightActor->transform.Rotate(ost::Quaternion::FromRotationAxis({1, 0, 0}, -45.0f * ost::math::DegToRad));
    rightActor->AddComponent<KeyboardRotatorComponent>();

    leftMeshComponent.SetModel(cubeModel);
    leftMeshComponent.SetMaterial(leatherMaterial);

    rightMeshComponent.SetModel(cubeModel);
    rightMeshComponent.SetMaterial(rockMaterial);

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 0.0f, -2.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    ost::Actor* lightActor = _scene->CreateActor();
    auto& sceneLight = lightActor->AddComponent<ost::SceneLightComponent>();
    sceneLight.SetSunDirection(ost::Vector3f(0.0f, -1.0f, 0.0f).GetNormalized());
    sceneLight.SetSunColor({4.0f, 4.0f, 4.0f, 1.0f});

    sceneLight.SetAmbientColor({0.0f, 0.01f, 0.02f, 1.0f});
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