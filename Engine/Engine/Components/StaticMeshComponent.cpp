// Kasper "OstGeneralen" Esbjornsson - 2026
#include "StaticMeshComponent.h"

#include "Engine/World/Actor.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

StaticMeshComponent::StaticMeshComponent(ModelHandle modelHandle)
    : _modelHandle{modelHandle}
{
}

// ------------------------------------------------------------

void StaticMeshComponent::InitializeRenderState(RenderGraph& renderGraph)
{
    StaticMeshRenderProxy renderProxy;
    renderProxy.hModel = _modelHandle;
    renderProxy.transform = GetOwner().transform.GetWorldTransform();
    _proxyMeshHandle = renderGraph.AddStaticMeshProxy(renderProxy);

    _pRenderGraph = &renderGraph;

    GetOwner().transform.OnMarkedDirty.Bind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);
}

void ost::StaticMeshComponent::DestroyRenderState(RenderGraph& renderGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);

    renderGraph.RemoveStaticMeshProxy(_proxyMeshHandle);
    _proxyMeshHandle = 0;
    _pRenderGraph = nullptr;
}

void ost::StaticMeshComponent::OnTransformMarkedDirty()
{
    _pRenderGraph->MarkTransformDirty(*this);
}

void ost::StaticMeshComponent::UpdateDirtyTransform(RenderGraph& renderGraph)
{
    // Update this now
    renderGraph.GetStaticMeshProxy(_proxyMeshHandle).transform = GetOwner().transform.GetWorldTransform();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------