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

    ost::HModel cubeModel = assets.LoadFromFile<ost::HModel>("Models/Cube", "Meshes/MaterialTestPlane.fbx");
    ost::HModel planeModel = assets.LoadFromFile<ost::HModel>("Models/Plane", "Meshes/PlaneTest.fbx");

    // Load our two textures
    ost::HTexture rockAlbedo = assets.LoadFromFile<ost::HTexture>("Textures/RockC", "Materials/Rock/Rock_Albedo.dds");
    ost::HTexture rockNormal = assets.LoadFromFile<ost::HTexture>("Textures/RockN", "Materials/Rock/Rock_Normal.dds");
    ost::HTexture rockORM = assets.LoadFromFile<ost::HTexture>("Textures/RockORM", "Materials/Rock/Rock_ORM.dds");

    ost::HTexture leatherAlbedo = assets.LoadFromFile<ost::HTexture>("Textures/LeatherC", "Materials/Leather/Leather_Albedo.dds");
    ost::HTexture leatherNormal = assets.LoadFromFile<ost::HTexture>("Textures/LeatherN", "Materials/Leather/Leather_Normal.dds");
    ost::HTexture leatherORM = assets.LoadFromFile<ost::HTexture>("Textures/LeatherORM", "Materials/Leather/Leather_ORM.dds");

    // Let's create our material + instances :)
    ost::IMaterial& material = assets.Create<ost::IMaterial>("Mat/Default", {ost::EMaterialDomain::SurfaceLit, "MaterialShaders/ColoredSurfaceLit.hlsl"});
    material.GetPropertyDefaults().SetProperty("OverrideColor", ost::Colors::White.Vec4);
    material.GetPropertyDefaults().SetProperty("OverrideStrength", 0.0f);

    // Now create the material instance we'll use
    {
        ost::IMaterialInstance& materialInstance = assets.Create<ost::IMaterialInstance>("Mat/Rock", assets.GetHandle<ost::IMaterial>("Mat/Default"));
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::Albedo, rockAlbedo);
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::Normal, rockNormal);
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::ORM, rockORM);
    }
    {
        ost::IMaterialInstance& materialInstance = assets.Create<ost::IMaterialInstance>("Mat/Leather", assets.GetHandle<ost::IMaterial>("Mat/Default"));
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::Albedo, leatherAlbedo);
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::Normal, leatherNormal);
        materialInstance.Textures().SetTexture(ost::EMaterialTexture::ORM, leatherORM);
    }

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
    leftMeshComponent.SetMaterial("Mat/Rock");

    rightMeshComponent.SetModel(cubeModel);
    rightMeshComponent.SetMaterial("Mat/Leather");

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