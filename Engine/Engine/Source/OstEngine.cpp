// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include "Engine/World/Scene.h"

#include <GraphicsEngine/IGraphicsEngine.h>
#include <GraphicsEngine/Rendering/IRenderQueue.h>
#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Utility/Assert.h>

// Components
#include "Engine/Components/CameraComponent.h"
#include "Engine/Components/DirectionalLightComponent.h"
#include "Engine/Components/PointLightComponent.h"
#include "Engine/Components/SpotLightComponent.h"
#include "Engine/Components/StaticMeshComponent.h"

// ------------------------------------------------------------

ost::IEngineGlobal* ost::pEngine = nullptr;

using namespace ost;
// ------------------------------------------------------------

UniquePtr<IOstEngine> IOstEngine::Create(ServiceLocator& services)
{
    UniquePtr<OstEngine> ptr = Ptr::NewUnique<OstEngine>(services);
    return ptr;
}

// ------------------------------------------------------------

OstEngine::OstEngine(ServiceLocator& appServiceLocator)
    : _appServiceLocator{appServiceLocator}
    , _input{}
    , _time{}
    , _assetManager{appServiceLocator}
    , _pGameInstance{nullptr}
{
    pEngine = this;

    // Register Engine Provided Component Types
    _componentFactory.RegisterComponentType("Camera", ComponentTypeRegistration::MakeForT<CameraComponent>());
    _componentFactory.RegisterComponentType("Static Mesh", ComponentTypeRegistration::MakeForT<StaticMeshComponent>());
    _componentFactory.RegisterComponentType("Directional Light", ComponentTypeRegistration::MakeForT<DirectionalLightComponent>());
    _componentFactory.RegisterComponentType("Point Light", ComponentTypeRegistration::MakeForT<PointLightComponent>());
    _componentFactory.RegisterComponentType("Spot Light", ComponentTypeRegistration::MakeForT<SpotLightComponent>());

    // Register Engine Services
    _appServiceLocator.RegisterUnmanaged<IInputReader>(&_input);
    _appServiceLocator.RegisterUnmanaged<ITimeProvider>(&_time);
    _appServiceLocator.RegisterUnmanaged<IAssetManager>(&_assetManager);
    _appServiceLocator.RegisterUnmanaged<ISceneManager>(&_sceneManager);
    _appServiceLocator.RegisterUnmanaged<IComponentFactory>(&_componentFactory);
}

OstEngine::~OstEngine()
{
    _appServiceLocator.Unregister<IInputReader>();
    _appServiceLocator.Unregister<ITimeProvider>();
    _appServiceLocator.Unregister<IAssetManager>();
    _appServiceLocator.Unregister<ISceneManager>();
    _appServiceLocator.Unregister<IComponentFactory>();

    pEngine = nullptr;
}

// ------------------------------------------------------------

void OstEngine::SetGameInstance(GameBase* pGameInstance)
{
    if (_pGameInstance)
    {
        _pGameInstance->Unload(_assetManager);
        _pGameInstance->Shutdown(_componentFactory);
    }

    _pGameInstance = pGameInstance;
    if (_pGameInstance)
    {
        _pGameInstance->Start(_componentFactory);
        _pGameInstance->Load(_assetManager);
    }
}

// ------------------------------------------------------------

void OstEngine::Tick()
{
    _time.Update();

    if (_pGameInstance)
    {
        _pGameInstance->Update(_time.GetDeltaTime());
    }

    _sceneManager.GetGameWorld().Tick(_appServiceLocator);

    _input.EndFrame();
}

void OstEngine::RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer)
{
    auto& sceneGraph = _sceneManager.GetGameWorld().GetSceneGraph();

    for (const auto& meshProxy : sceneGraph.GetStaticMeshProxies())
    {
        toQueue.Push(ModelCommand(meshProxy.hModel, meshProxy.materialHandles, meshProxy.transform));
    }

    for (const auto& lightProxy : sceneGraph.GetLightProxies())
    {
        LightCommand cmd;
        cmd.cmdData = lightProxy.proxyData;
        toQueue.Push(std::move(cmd));
    }

    const ViewRenderProxy& viewProxy = sceneGraph.GetViewProxy();

    Matrix4x4 projection;
    switch (viewProxy.projectionType)
    {
    case ViewRenderProxy::EProjectionType::Perspective: {
        projection = Matrix4x4::CreatePerspectiveProjection(viewProxy.lValue, targetRenderer.GetAspectRatio(), 0.1f, 30.0f);
        break;
    }
    case ViewRenderProxy::EProjectionType::Orthographic: {
        projection = Matrix4x4::CreateOrthographicsProjection(viewProxy.lValue * targetRenderer.GetDimensions().X, viewProxy.rValue * targetRenderer.GetDimensions().Y,
                                                              0.1f, 30.0f);
        break;
    }
    }
    const Matrix4x4 toView = viewProxy.transform.GetInverse();
    const Matrix4x4 proj = projection;
    toQueue.SetView(toView * proj, viewProxy.transform);
}

InputReader& OstEngine::GetInputReader()
{
    return _input;
}

ServiceLocator& ost::OstEngine::GetServiceLocator()
{
    return _appServiceLocator;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------