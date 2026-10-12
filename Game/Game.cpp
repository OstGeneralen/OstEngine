// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

#include <Engine/Asset/IAssetManager.h>
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

    // Load our two textures
    ost::HTexture albedo = context.Assets().LoadTextureFromFile("Materials/Rock/Rock_Albedo.dds");
    ost::HTexture normalMap = context.Assets().LoadTextureFromFile("Materials/Rock/Rock_Normal.dds");

    // Load the debug shape mesh
    ost::HModel plane = context.Assets().LoadModelFromFile("Meshes/MaterialTestPlane.fbx");

    // Let's create our material + instances :)
    ost::HMaterial materialHandle = context.Assets().CreateMaterial(ost::EMaterialDomain::SurfaceLit, "MaterialShaders/ColoredSurfaceLit.hlsl");
    ost::IMaterial& material = context.Assets().GetMaterial(materialHandle);
    material.GetPropertyDefaults().SetProperty("OverrideColor", ost::Colors::White.Vec4);
    material.GetPropertyDefaults().SetProperty("OverrideStrength", 0.0f);

    // Now create the material instance we'll use
    ost::HMaterialInstance materialInstanceHandle = context.Assets().CreateMaterialInstance(materialHandle);
    ost::IMaterialInstance& materialInstance = context.Assets().GetMaterialInstance(materialInstanceHandle);
    materialInstance.Textures().SetTexture(ost::EMaterialTexture::Albedo, albedo);
    materialInstance.Textures().SetTexture(ost::EMaterialTexture::Normal, normalMap);

    // Now let's create the plane actor
    ost::Actor* planeActor = _scene->CreateActor();
    auto& planeMeshComponent = planeActor->AddComponent<ost::StaticMeshComponent>();
    planeMeshComponent.SetModel(plane);
    planeMeshComponent.SetMaterial(materialInstanceHandle);
    planeActor->transform.Rotate(ost::Quaternion::FromRotationAxis({1, 0, 0}, -45.0f * ost::math::DegToRad));
    planeActor->AddComponent<KeyboardRotatorComponent>();

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 0.0f, -4.0f}, ost::ESpace::World);
    //cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    ost::Actor* lightActor = _scene->CreateActor();
    auto& sceneLight = lightActor->AddComponent<ost::SceneLightComponent>();
    sceneLight.SetSunDirection(ost::Vector3f(3.0f, -3.0f, 2.0f).GetNormalized());
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