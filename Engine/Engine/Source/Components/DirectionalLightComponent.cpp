// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/DirectionalLightComponent.h"

#include "Engine/World/Actor.h"
#include "Engine/World/IComponentInitializer.h"
#include "Engine/World/SceneGraph.h"
#include "Engine/World/Transform.h"

using namespace ost;

// ------------------------------------------------------------

DirectionalLightComponent::DirectionalLightComponent()
    : RenderComponent()
    , _pSceneGraph{nullptr}
{
}

void ost::DirectionalLightComponent::SetColor(const Color& color, Float32 intensity)
{
    if (_pSceneGraph)
    {
        _pSceneGraph->GetLightProxy(_hSceneProxy).color.Vec4 = color.Vec4 * intensity;
    }
}

void DirectionalLightComponent::Initialize(IComponentInitializer& initializer)
{
    RenderComponent::Initialize(initializer);
    initializer.InitializeAsRenderComponent(*this);
}

void ost::DirectionalLightComponent::InitializeRenderState(SceneGraph& sceneGraph)
{
    _pSceneGraph = &sceneGraph;
    GetOwner().transform.OnMarkedDirty.Bind<DirectionalLightComponent, &DirectionalLightComponent::OnTransformDirty>(this);

    LightRenderProxy proxy;
    proxy.type = ELightProxyType::Directional;
    proxy.direction = GetOwner().transform.GetForward();
    proxy.color = Colors::White;
    _hSceneProxy = sceneGraph.AddLightProxy(proxy);
}

void ost::DirectionalLightComponent::DestroyRenderState(SceneGraph& sceneGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<DirectionalLightComponent, &DirectionalLightComponent::OnTransformDirty>(this);

    sceneGraph.RemoveLightProxy(_hSceneProxy);
    _hSceneProxy = 0;
    _pSceneGraph = nullptr;
}

void ost::DirectionalLightComponent::UpdateDirtyTransform(SceneGraph& sceneGraph)
{
    sceneGraph.GetLightProxy(_hSceneProxy).direction = GetOwner().transform.GetForward();
}

void ost::DirectionalLightComponent::OnTransformDirty()
{
    if (_pSceneGraph)
    {
        _pSceneGraph->MarkTransformDirty(*this);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------