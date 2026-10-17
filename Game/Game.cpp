// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Game.h"

#include "DebugMaterialToggleComponent.h"
#include "KeyboardMovementComponent.h"
#include "KeyboardRotatorComponent.h"

#include <Engine/Asset/IAssetManager.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/DirectionalLightComponent.h>
#include <Engine/Components/PointLightComponent.h>
#include <Engine/Components/SpotLightComponent.h>
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

    ost::HModel roomModel = assets.Load<ost::HModel>("Game/LightRoom");
    assets.Load<ost::IMaterial>("Engine/Mat_DefaultLit");

    // Now create the material instance we'll use
    ost::HMaterialInstance materialInstances[4];
    materialInstances[0] = assets.Load<ost::IMaterialInstance>("Game/RockMaterial");
    materialInstances[1] = assets.Load<ost::IMaterialInstance>("Game/LeatherMaterial");
    materialInstances[2] = assets.Load<ost::IMaterialInstance>("Game/MossMaterial");
    materialInstances[3] = assets.Load<ost::IMaterialInstance>("Game/MetalMaterial");

    ost::HMaterialInstance rockMaterial = materialInstances[0];
    ost::HMaterialInstance leatherMaterial = materialInstances[1];

    // The actor
    // ost::Actor* meshActor = _scene->CreateActor();
    // auto& meshComponent = meshActor->AddComponent<ost::StaticMeshComponent>();
    // meshComponent.SetModel(multiMaterialModel);
    // meshComponent.SetMaterial(materialInstances[0], 0);
    // meshComponent.SetMaterial(materialInstances[1], 1);
    // meshComponent.SetMaterial(materialInstances[3], 2);
    // meshActor->transform.SetPosition({0, -1, 0});

    // for (Uint32 i = 0; i < 4; ++i)
    //{
    //     ost::Actor* actor = _scene->CreateActor();
    //
    //    auto& meshComponent = actor->AddComponent<ost::StaticMeshComponent>();
    //    meshComponent.SetModel(planeModel);
    //    meshComponent.SetMaterial(materialInstances[i]);
    //
    //    actor->AddComponent<DebugMaterialToggleComponent>();
    //
    //    Float32 xOffset = (static_cast<Float32>(i) - 2.0f) * 2.0f;
    //    actor->transform.SetPosition({xOffset, 0, 0});
    //    actor->transform.Rotate(ost::Quaternion::FromRotationAxis(actor->transform.GetRight() * -1.0f, 45.0f * ost::math::DegToRad));
    //}

    ost::Actor* meshActor = _scene->CreateActor();
    auto& staticMeshComp = meshActor->AddComponent<ost::StaticMeshComponent>();
    staticMeshComp.SetModel(roomModel);
    staticMeshComp.SetMaterial(rockMaterial, 0);
    staticMeshComp.SetMaterial(leatherMaterial, 1);
    meshActor->transform.SetPosition({0, 0, 0});

    ost::Actor* sunActor = _scene->CreateActor();
    auto& sunLight = sunActor->AddComponent<ost::DirectionalLightComponent>();
    sunLight.SetColor(ost::Colors::White);
    sunLight.SetIntensity(1.0f);

    ost::Quaternion rotation = ost::Quaternion::FromEulers( 45.0f * ost::math::DegToRad, 0, 0 );
    sunActor->transform.Rotate(rotation);

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 1.0f, 0.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    pLightActor = _scene->CreateActor();

    ost::Color colors[3] = {ost::Colors::Red, ost::Colors::Green, ost::Colors::Blue};
    ost::Vector3f positions[3] = {{-2.5f, 2.0f, 1.0f}, {0.0f, 2.0f, 1.0f}, {2.5f, 2.0f, 1.0f}};

    for (SizeType i = 0; i < 3; ++i)
    {
        ost::Actor* pointLightActor = _scene->CreateActor();
        auto& pointLight = pointLightActor->AddComponent<ost::SpotLightComponent>();
        pointLight.SetColor(ost::Colors::White);
        pointLight.SetIntensity(3.0f);
        pointLight.SetRange(10.0f);
        pointLight.SetInnerRadius(0.1f);
        pointLight.SetOuterRadius(0.6f);
        pointLightActor->transform.SetPosition(positions[i]);
        pointLightActor->transform.Rotate(ost::Quaternion::FromEulers({90.0f * ost::math::DegToRad, 0, 0}));
    }

    // ost::Actor* spotActor = _scene->CreateActor();
    // auto& spotLight = spotActor->AddComponent<ost::SpotLightComponent>();
    // spotLight.SetColor(ost::Colors::White);
    // spotLight.SetIntensity(3.0f);
    // spotLight.SetInnerRadius(0.05f);
    // spotLight.SetOuterRadius(0.35f);
    // spotLight.SetRange(8.0f);
    // spotActor->transform.SetPosition({-3, 1, 0.9f});
    // spotActor->transform.SetRotation(ost::Quaternion::FromEulers({0, 90.0f * ost::math::DegToRad, 0.0f}));
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