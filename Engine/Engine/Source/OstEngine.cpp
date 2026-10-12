// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include "Engine/Game/GameInterface.h"
#include "Engine/World/Scene.h"

#include <GraphicsEngine/Rendering/IRenderQueue.h>
#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

UniquePtr<IOstEngine> IOstEngine::CreateNew(OstEngineSettings&& settings)
{
    UniquePtr<OstEngine> ptr = Ptr::NewUnique<OstEngine>();
    ptr->Initialize(std::move(settings.gameInstance), *settings.pGfxResourceManager, *settings.pMaterialManager);
    return ptr;
}

// ------------------------------------------------------------

OstEngine::OstEngine()
    : _timer{}
    , _gameWorld{}
    , _input{}
    , _assetManager{}
    , _engineContext{_assetManager}
    , _gameContext{*this}
    , _gameInstance{}
    , _pActiveScene{nullptr}
{
}

OstEngine::~OstEngine()
{
}

// ------------------------------------------------------------

void OstEngine::Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager)
{
    _assetManager.Initialize(gfxResourceManager, materialManager);

    _gameInstance = std::move(gameInstance);
    _gameInstance->Load(_gameContext);
}

// ------------------------------------------------------------

void OstEngine::Tick()
{
    _timer.Tick();

    _gameInstance->Update(_gameContext);

    ComponentContext componentContext{_timer, _input};
    _gameWorld.Tick(componentContext);

    _input.EndFrame();
}

void OstEngine::RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer)
{
    for (const auto& meshProxy : _gameWorld.GetSceneGraph().GetStaticMeshProxies())
    {
        toQueue.Push(ModelCommand(meshProxy.hModel, meshProxy.hMaterial, meshProxy.transform));
    }

    for (const auto& lightProxy : _gameWorld.GetSceneGraph().GetLightProxies())
    {
        switch (lightProxy.type)
        {
        case ELightProxyType::Directional:
            toQueue.Push(LightCommand::Directional(lightProxy.direction, lightProxy.color));
            break;
        case ELightProxyType::Ambient:
            toQueue.Push(LightCommand::Ambient(lightProxy.color));
            break;
        }
    }

    const ViewRenderProxy& viewProxy = _gameWorld.GetSceneGraph().GetViewProxy();

    Matrix4x4 projection;
    switch (viewProxy.projectionType)
    {
    case ViewRenderProxy::EProjectionType::Perspective: {
        projection = Matrix4x4::CreatePerspectiveProjection(viewProxy.lValue, targetRenderer.GetAspectRatio(), 0.1f, 100000.0f);
        break;
    }
    case ViewRenderProxy::EProjectionType::Orthographic: {
        projection = Matrix4x4::CreateOrthographicsProjection(viewProxy.lValue * targetRenderer.GetDimensions().X, viewProxy.rValue * targetRenderer.GetDimensions().Y,
                                                              0.1f, 100000.0f);
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

// ------------------------------------------------------------
// Game Context

OstGameContext::OstGameContext(OstEngine& instance)
    : _engineInstance{instance}
{
}

UniquePtr<Scene> OstGameContext::CreateScene(bool makeActive)
{
    UniquePtr<Scene> created = Ptr::NewUnique<Scene>(_engineInstance._gameWorld);
    if (makeActive)
    {
        _engineInstance._pActiveScene = created.Get();
    }
    return created;
}

void OstGameContext::SetActiveScene(Scene& scene)
{
    _engineInstance._pActiveScene = &scene;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------