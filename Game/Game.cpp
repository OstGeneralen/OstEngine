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
    ost::HModel multiMaterialModel = assets.Load<ost::HModel>("Game/MultiMaterialModel");

    assets.Load<ost::IMaterial>("Engine/Mat_DefaultLit");

    // Now create the material instance we'll use
    ost::HMaterialInstance materialInstances[4];
    materialInstances[0] = assets.Load<ost::IMaterialInstance>("Game/RockMaterial");
    materialInstances[1] = assets.Load<ost::IMaterialInstance>("Game/LeatherMaterial");
    materialInstances[2] = assets.Load<ost::IMaterialInstance>("Game/MossMaterial");
    materialInstances[3] = assets.Load<ost::IMaterialInstance>("Game/MetalMaterial");

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

    // Let there be eyes
    ost::Actor* cameraActor = _scene->CreateActor();
    auto& camera = cameraActor->AddComponent<ost::CameraComponent>();
    camera.MakePerspective(75.0f * ost::math::DegToRad);
    cameraActor->transform.Move({0.0f, 1.0f, 0.0f}, ost::ESpace::World);
    cameraActor->AddComponent<KeyboardMovementComponent>();

    // Let there be light
    pLightActor = _scene->CreateActor();

    ost::Color colors[6] = {ost::Colors::Red, ost::Colors::Green, ost::Colors::Blue, ost::Colors::Yellow, ost::Colors::Magenta, ost::Colors::Cyan};
    Float32 radiis[5] = {2.3f, 1.5f, 2.0f, 1.8f, 1.1f};
    Float32 intensities[3] = {1.5f, 2.0f, 2.3f};

    for (SizeType i = 0; i < 34; ++i)
    {
        const Float32 x = static_cast<Float32>(i % 8) * 2.0f;
        const Float32 z = static_cast<Float32>(i / 8) * 2.0f;

        ost::Actor* pointLightActor = _scene->CreateActor();
        auto& pointLight = pointLightActor->AddComponent<ost::PointLightComponent>();
        pointLight.SetColor(colors[i % 6]);
        pointLight.SetIntensity(intensities[i % 3]);
        pointLight.SetRadius(radiis[i % 5]);
        pointLightActor->transform.SetPosition({x, 1.0f, z});

        ost::Actor* meshActor = _scene->CreateActor();
        auto& meshComponent = meshActor->AddComponent<ost::StaticMeshComponent>();
        meshComponent.SetModel(planeModel);
        meshComponent.SetMaterial(materialInstances[0], 0);
        meshActor->transform.SetPosition({x, 0, z});
    }
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