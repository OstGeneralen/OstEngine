// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "DebugMaterialToggleComponent.h"
#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

#include <Engine/Asset/IAssetManager.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/DirectionalLightComponent.h>
#include <Engine/Components/PointLightComponent.h>
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

    assets.Load<ost::IMaterial>("Engine/Mat_DefaultLit");

    // Now create the material instance we'll use
    ost::HMaterialInstance materialInstances[4];
    materialInstances[0] = assets.Load<ost::IMaterialInstance>("Game/RockMaterial");
    materialInstances[1] = assets.Load<ost::IMaterialInstance>("Game/LeatherMaterial");
    materialInstances[2] = assets.Load<ost::IMaterialInstance>("Game/MossMaterial");
    materialInstances[3] = assets.Load<ost::IMaterialInstance>("Game/MetalMaterial");

    for (Uint32 i = 0; i < 4; ++i)
    {
        ost::Actor* actor = _scene->CreateActor();

        auto& meshComponent = actor->AddComponent<ost::StaticMeshComponent>();
        meshComponent.SetModel(planeModel);
        meshComponent.SetMaterial(materialInstances[i]);

        actor->AddComponent<DebugMaterialToggleComponent>();

        Float32 xOffset = (static_cast<Float32>(i) - 2.0f) * 2.0f;
        actor->transform.SetPosition({xOffset, 0, 0});
        actor->transform.Rotate(ost::Quaternion::FromRotationAxis(actor->transform.GetRight() * -1.0f, 45.0f * ost::math::DegToRad));
    }

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 0.0f, -4.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    pLightActor = _scene->CreateActor();
    auto& directionalLight = pLightActor->AddComponent<ost::DirectionalLightComponent>();
    directionalLight.SetColor(ost::Color(1.0f, 0.9f, 0.7f, 1.0f));
    directionalLight.SetIntensity(2.0f);
    pLightActor->transform.SetRotation(ost::Quaternion::FromEulers({1, 0, 0}));
    pLightActor->AddComponent<KeyboardRotatorComponent>();

    ost::Actor* pointLightActor = _scene->CreateActor();
    auto& pointLight = pointLightActor->AddComponent<ost::PointLightComponent>();
    pointLight.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
    pointLight.SetIntensity(1.0f);
    pointLight.SetRadius(4.0f);
    pointLightActor->transform.SetPosition({0, 1, 0});
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