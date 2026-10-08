// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include "Engine/World/Scene.h"
#include "Game/GameInterface.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

OstEngine::OstEngine()
{
}

OstEngine::~OstEngine()
{
}

void OstEngine::Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager)
{
    _gfxAssetManager.SetResourceManager(gfxResourceManager);

    _gameInstance = std::move(gameInstance);
    _gameInstance->Load(*this);
}

void OstEngine::Tick()
{
    _timer.Tick();

    _gameInstance->Update(*this);

    ComponentContext componentContext{_timer, _input};
    _gameWorld.Tick(componentContext);

    _input.EndFrame();
}

void OstEngine::RenderScene(IRenderer& renderer)
{
    for (const auto& meshProxy : _gameWorld.GetRenderGraph().GetStaticMeshProxies())
    {
        renderer.PushRenderCommand(meshProxy.hModel, meshProxy.transform);
    }

    for (const auto& lightProxy : _gameWorld.GetRenderGraph().GetLightProxies())
    {
        RenderLight cmd;

        switch (lightProxy.type)
        {
        case ELightProxyType::Directional: {

            cmd.lightType = ELightType::Directional;
            cmd.direction = lightProxy.direction;
            cmd.color = lightProxy.color;
            break;
        }
        case ELightProxyType::Ambient: {
            cmd.lightType = ELightType::Ambient;
            cmd.color = lightProxy.color;
            break;
        }
        }

        renderer.PushLightCommand(cmd);
    }

    const ViewRenderProxy& viewProxy = _gameWorld.GetRenderGraph().GetViewProxy();
    const Vector2f renderDimensions = renderer.GetRenderDimensions();

    Matrix4x4 projection;
    switch (viewProxy.projectionType)
    {
    case ViewRenderProxy::EProjectionType::Perspective: {
        projection = Matrix4x4::CreatePerspectiveProjection(viewProxy.lValue, renderDimensions.X / renderDimensions.Y, 0.1f, 100000.0f);
        break;
    }
    case ViewRenderProxy::EProjectionType::Orthographic: {
        projection = Matrix4x4::CreateOrthographicsProjection(viewProxy.lValue * renderDimensions.X, viewProxy.rValue * renderDimensions.Y, 0.1f, 100000.0f);
        break;
    }
    }

    Matrix4x4 viewProjection = viewProxy.transform.GetInverse() * projection;
    renderer.ExecuteRenderCommands(viewProjection);
}

InputReader& OstEngine::GetInputReader()
{
    return _input;
}

// ------------------------------------------------------------
// Engine Context

GraphicsAssetsManager& OstEngine::AssetManager()
{
    return _gfxAssetManager;
}

const TimeStructure& ost::OstEngine::Time() const
{
    return _timeData;
}

UniquePtr<Scene> OstEngine::CreateScene(bool makeActive)
{
    UniquePtr<Scene> created = Ptr::NewUnique<Scene>(_gameWorld);
    if (makeActive)
    {
        _pActiveScene = created.Get();
    }
    return created;
}

void OstEngine::SetActiveScene(Scene& scene)
{
    _pActiveScene = &scene;
}

const InputReader& OstEngine::GetInput() const
{
    return _input;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------