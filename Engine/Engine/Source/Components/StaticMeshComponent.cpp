// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/StaticMeshComponent.h"

#include "Engine/Asset/IAssetManager.h"
#include "Engine/World/Actor.h"
#include "World/SceneGraph.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void ost::StaticMeshComponent::SetModel(const AssetRef<Model>& model)
{
    for (auto proxyHandle : _meshProxyHandles)
    {
        _pSceneGraph->RemoveStaticMeshProxy(proxyHandle);
    }
    _meshProxyHandles.Clear();

    _model = model;

    if (_model)
    {
        for (auto submesh : _model->GetSubmeshes())
        {
            StaticMeshRenderProxy proxy;
            proxy.indexBuffer = _model->GetIndexBuffer();
            proxy.vertexBuffer = _model->GetVertexBuffer();
            proxy.transform = GetOwner().transform.GetWorldTransform();
            proxy.indexCount = submesh.indexCount;
            proxy.indexOffset = submesh.indexOffset;
            proxy.vertexCount = submesh.vertexCount;
            _meshProxyHandles.Add(_pSceneGraph->AddStaticMeshProxy(proxy));
        }
    }
}

// ------------------------------------------------------------

void StaticMeshComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    _pSceneGraph = &SceneGraph;

    GetOwner().transform.OnMarkedDirty.Bind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);
}

void ost::StaticMeshComponent::DestroyRenderState(SceneGraph& SceneGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<StaticMeshComponent, &StaticMeshComponent::OnTransformMarkedDirty>(this);
    SetModel(AssetRef<Model>()); // Set to a null model ref to release all proxies
    _pSceneGraph = nullptr;
}

void ost::StaticMeshComponent::OnTransformMarkedDirty()
{
    _pSceneGraph->MarkTransformDirty(*this);
}

void ost::StaticMeshComponent::UpdateDirtyTransform(SceneGraph& SceneGraph)
{
    // Update this now
    const Matrix4x4 transform = GetOwner().transform.GetWorldTransform();
    for (auto proxyHandle : _meshProxyHandles)
    {
        _pSceneGraph->GetStaticMeshProxy(proxyHandle).transform = transform;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------