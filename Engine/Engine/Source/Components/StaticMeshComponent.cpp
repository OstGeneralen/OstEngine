// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/StaticMeshComponent.h"

#include "Engine/Asset/IAssetManager.h"
#include "Engine/EngineContext.h"
#include "Engine/World/Actor.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void StaticMeshComponent::SetModel(HModel hnd)
{
    if (_pSceneGraph)
    {
        _pSceneGraph->GetStaticMeshProxy(_proxyMeshHandle).hModel = hnd;
    }
}

void StaticMeshComponent::SetModel(const std::string& modelName)
{
    SetModel(EngineContext::Get().Assets().GetHandle<HModel>(modelName));
}

void StaticMeshComponent::SetMaterial(HMaterialInstance hnd)
{
    if (_pSceneGraph)
    {
        _pSceneGraph->GetStaticMeshProxy(_proxyMeshHandle).hMaterial = hnd;
    }
}

void StaticMeshComponent::SetMaterial(const std::string& materialName)
{
    SetMaterial(EngineContext::Get().Assets().GetHandle<IMaterialInstance>(materialName));
}
// ------------------------------------------------------------

void StaticMeshComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    StaticMeshRenderProxy renderProxy;
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