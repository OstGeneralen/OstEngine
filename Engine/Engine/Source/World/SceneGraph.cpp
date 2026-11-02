// Kasper "OstGeneralen" Esbjornsson - 2026
#include "World/SceneGraph.h"

#include "Engine/World/Component.h"

#include <GraphicsEngine/Rendering/IRenderQueue.h>
#include <GraphicsEngine/Rendering/IRenderer.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

ProxyHandle SceneGraph::AddStaticMeshProxy(const StaticMeshRenderProxy& proxy)
{
    return _meshProxies.Add(proxy);
}

StaticMeshRenderProxy& SceneGraph::GetStaticMeshProxy(ProxyHandle handle)
{
    return _meshProxies[handle];
}

void SceneGraph::RemoveStaticMeshProxy(ProxyHandle handle)
{
    _meshProxies.Remove(handle);
}

// ------------------------------------------------------------

ProxyHandle SceneGraph::AddLightProxy(const LightRenderProxy& proxy)
{
    return _lightProxies.Add(proxy);
}

LightRenderProxy& SceneGraph::GetLightProxy(ProxyHandle handle)
{
    return _lightProxies[handle];
}

void SceneGraph::RemoveLightProxy(ProxyHandle handle)
{
    _lightProxies.Remove(handle);
}

// ------------------------------------------------------------

ViewRenderProxy& SceneGraph::GetViewProxy()
{
    return _viewProxy;
}

// ------------------------------------------------------------

const ViewRenderProxy& SceneGraph::GetViewProxy() const
{
    return _viewProxy;
}

// ------------------------------------------------------------

void SceneGraph::MarkTransformDirty(RenderComponent& renderComponent)
{
    _pendingTransformReevaluations.Add(&renderComponent);
}

void SceneGraph::ReconcileTransforms()
{
    for (auto rc : _pendingTransformReevaluations)
    {
        rc->UpdateDirtyTransform(*this);
    }

    _pendingTransformReevaluations.Clear();
}

// ------------------------------------------------------------

void ost::SceneGraph::PopulateRenderQueue(IRenderQueue& toQueue, const IRenderer& targetRenderer) const
{
    for (const auto& meshProxy : _meshProxies)
    {
        if (meshProxy.hModel)
        {
            toQueue.Push(ModelCommand(meshProxy.hModel, meshProxy.materialHandles, meshProxy.transform));
        }
    }

    for (const auto& lightProxy : _lightProxies)
    {
        LightCommand cmd;
        cmd.cmdData = lightProxy.proxyData;
        toQueue.Push(std::move(cmd));
    }

    Matrix4x4 projection;
    switch (_viewProxy.projectionType)
    {
    case ViewRenderProxy::EProjectionType::Perspective: {
        projection = Matrix4x4::CreatePerspectiveProjection(_viewProxy.lValue, targetRenderer.GetAspectRatio(), 0.1f, 30.0f);
        break;
    }
    case ViewRenderProxy::EProjectionType::Orthographic: {
        projection = Matrix4x4::CreateOrthographicsProjection(_viewProxy.lValue * targetRenderer.GetDimensions().X, _viewProxy.rValue * targetRenderer.GetDimensions().Y,
                                                              0.1f, 30.0f);
        break;
    }
    case ViewRenderProxy::EProjectionType::Unset: {
        projection = Matrix4x4(); // Simple identity
        break;
    }
    }

    const Matrix4x4 toView = _viewProxy.transform.GetInverse();
    const Matrix4x4 proj = projection;
    toQueue.SetView(toView * proj, _viewProxy.transform);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------