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
    ptr->Initialize(std::move(settings.gameInstance), *settings.pGfxResourceManager);
    return ptr;
}

// ------------------------------------------------------------

OstEngine::OstEngine()
    : _context{*this}
{
}

OstEngine::~OstEngine()
{
}

// ------------------------------------------------------------

void OstEngine::Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager)
{
    _assetManager.Initialize(gfxResourceManager);

    _gameInstance = std::move(gameInstance);
    _gameInstance->Load(_context);
}

// ------------------------------------------------------------

void OstEngine::Tick()
{
    _timer.Tick();

    _gameInstance->Update(_context);

    ComponentContext componentContext{_timer, _input};
    _gameWorld.Tick(componentContext);

    _input.EndFrame();
}

void OstEngine::RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer)
{
    for (const auto& meshProxy : _gameWorld.GetSceneGraph().GetStaticMeshProxies())
    {
        toQueue.Push(ModelCommand(meshProxy.hModel, meshProxy.transform));
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

    const Matrix4x4 view = viewProxy.transform.GetInverse();
    const Matrix4x4 proj = projection;
    toQueue.SetView(view * proj);
}

InputReader& OstEngine::GetInputReader()
{
    return _input;
}

// ------------------------------------------------------------
// Engine Context

OstEngineContext::OstEngineContext(OstEngine& instance)
    : _engineInstance{instance}
{
}

IAssetManager& OstEngineContext::Assets()
{
    return _engineInstance._assetManager;
}

const TimeStructure& ost::OstEngineContext::Time() const
{
    return _engineInstance._timeData;
}

UniquePtr<Scene> OstEngineContext::CreateScene(bool makeActive)
{
    UniquePtr<Scene> created = Ptr::NewUnique<Scene>(_engineInstance._gameWorld);
    if (makeActive)
    {
        _engineInstance._pActiveScene = created.Get();
    }
    return created;
}

void OstEngineContext::SetActiveScene(Scene& scene)
{
    _engineInstance._pActiveScene = &scene;
}

const InputReader& OstEngineContext::GetInput() const
{
    return _engineInstance._input;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------