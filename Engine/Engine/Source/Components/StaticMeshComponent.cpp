// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/StaticMeshComponent.h"

#include "Engine/World/Actor.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

StaticMeshComponent::StaticMeshComponent(ModelHandle modelHandle)
    : _modelHandle{modelHandle}
{
}

// ------------------------------------------------------------

void StaticMeshComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    StaticMeshRenderProxy renderProxy;
    renderProxy.hModel = _modelHandle;
    renderProxy.transform = GetOwner().transform.GetWorldTransform();
    _proxyMeshHandle = SceneGraph.AddStaticMeshProxy(renderProxy);

    _pSceneGraph = &SceneGraph;

    GetOwner().transform.OnMarkedDirty.Bind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);
}

void ost::StaticMeshComponent::DestroyRenderState(SceneGraph& SceneGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);

    SceneGraph.RemoveStaticMeshProxy(_proxyMeshHandle);
    _proxyMeshHandle = 0;
    _pSceneGraph = nullptr;
}

void ost::StaticMeshComponent::OnTransformMarkedDirty()
{
    _pSceneGraph->MarkTransformDirty(*this);
}

void ost::StaticMeshComponent::UpdateDirtyTransform(SceneGraph& SceneGraph)
{
    // Update this now
    SceneGraph.GetStaticMeshProxy(_proxyMeshHandle).transform = GetOwner().transform.GetWorldTransform();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------