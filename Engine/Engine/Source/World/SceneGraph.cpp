// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/SceneGraph.h"

#include "Engine/World/Component.h"

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

const List<StaticMeshRenderProxy>& SceneGraph::GetStaticMeshProxies() const
{
    return _meshProxies.GetDenseList();
}

const List<LightRenderProxy>& SceneGraph::GetLightProxies() const
{
    return _lightProxies.GetDenseList();
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
// ------------------------------------------------------------
// ------------------------------------------------------------