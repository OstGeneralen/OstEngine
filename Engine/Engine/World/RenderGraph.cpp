// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderGraph.h"

#include "Component.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

ProxyHandle RenderGraph::AddStaticMeshProxy(const StaticMeshRenderProxy& proxy)
{
    return _meshProxies.Add(proxy);
}

StaticMeshRenderProxy& RenderGraph::GetStaticMeshProxy(ProxyHandle handle)
{
    return _meshProxies[handle];
}

void RenderGraph::RemoveStaticMeshProxy(ProxyHandle handle)
{
    _meshProxies.Remove(handle);
}

// ------------------------------------------------------------

ProxyHandle RenderGraph::AddLightProxy(const LightRenderProxy& proxy)
{
    return _lightProxies.Add(proxy);
}

LightRenderProxy& RenderGraph::GetLightProxy(ProxyHandle handle)
{
    return _lightProxies[handle];
}

void RenderGraph::RemoveLightProxy(ProxyHandle handle)
{
    _lightProxies.Remove(handle);
}

// ------------------------------------------------------------

ViewRenderProxy& RenderGraph::GetViewProxy()
{
    return _viewProxy;
}

// ------------------------------------------------------------

const ViewRenderProxy& RenderGraph::GetViewProxy() const
{
    return _viewProxy;
}

const List<StaticMeshRenderProxy>& RenderGraph::GetStaticMeshProxies() const
{
    return _meshProxies.GetDenseList();
}

const List<LightRenderProxy>& RenderGraph::GetLightProxies() const
{
    return _lightProxies.GetDenseList();
}

// ------------------------------------------------------------

void RenderGraph::MarkTransformDirty(RenderComponent& renderComponent)
{
    _pendingTransformReevaluations.Add(&renderComponent);
}

void RenderGraph::ReconcileTransforms()
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