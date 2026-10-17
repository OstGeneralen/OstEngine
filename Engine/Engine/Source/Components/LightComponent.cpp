// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/LightComponent.h"

#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

void LightComponent::SetColor(const Color& color)
{
    GetProxy().proxyData.color = color;
}

const Color& ost::LightComponent::GetColor() const
{
    return GetProxy().proxyData.color;
}

void ost::LightComponent::SetIntensity(Float32 intensity)
{
    GetProxy().proxyData.intensity = intensity;
}

Float32 ost::LightComponent::GetIntensity() const
{
    return GetProxy().proxyData.intensity;
}

// ------------------------------------------------------------

void LightComponent::InitializeRenderState(SceneGraph& sceneGraph)
{
    _pSceneGraph = &sceneGraph;

    LightRenderProxy renderProxy = {};
    _proxyHandle = sceneGraph.AddLightProxy(renderProxy);

    GetOwner().transform.OnMarkedDirty.Bind<LightComponent, &LightComponent::NotifyTransformChanged>(this);

    // Call through to each individual light type and init their properties
    InitializeLightType(GetProxy());
}

void LightComponent::DestroyRenderState(SceneGraph& sceneGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<LightComponent, &LightComponent::NotifyTransformChanged>(this);
    sceneGraph.RemoveLightProxy(_proxyHandle);
    _pSceneGraph = nullptr;
}

// ------------------------------------------------------------

void LightComponent::UpdateDirtyTransform(SceneGraph& sceneGraph)
{
    GetProxy().proxyData.position = GetOwner().transform.GetWorldPosition();
    GetProxy().proxyData.direction = GetOwner().transform.GetForward();
}

LightRenderProxy& ost::LightComponent::GetProxy() const
{
    return _pSceneGraph->GetLightProxy(_proxyHandle);
}

void ost::LightComponent::NotifyTransformChanged()
{
    if (_pSceneGraph)
    {
        _pSceneGraph->MarkTransformDirty(*this);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------