// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/SceneLightComponent.h"

using namespace ost;

// ------------------------------------------------------------

void ost::SceneLightComponent::SetSunDirection(const Vector3f& direction)
{
    _sunDirection = direction;
    if (_pSceneGraph)
    {
        _pSceneGraph->GetLightProxy(_directionalLightProxyHandle).direction = _sunDirection;
    }
}

void ost::SceneLightComponent::SetAmbientColor(const Color& color)
{
    _ambientColor = color;
    if (_pSceneGraph)
    {
        _pSceneGraph->GetLightProxy(_ambientLightProxyHandle).color = _ambientColor;
    }
}

// ------------------------------------------------------------

void SceneLightComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    _pSceneGraph = &SceneGraph;

    LightRenderProxy dirProxy;
    dirProxy.direction = _sunDirection;
    dirProxy.type = ELightProxyType::Directional;
    dirProxy.color = Colors::White;
    _directionalLightProxyHandle = SceneGraph.AddLightProxy(dirProxy);

    LightRenderProxy ambProxy;
    ambProxy.color = _ambientColor;
    ambProxy.type = ELightProxyType::Ambient;
    _ambientLightProxyHandle = SceneGraph.AddLightProxy(ambProxy);
}

void SceneLightComponent::DestroyRenderState(SceneGraph& SceneGraph)
{
    SceneGraph.RemoveLightProxy(_directionalLightProxyHandle);
    _directionalLightProxyHandle = 0;

    SceneGraph.RemoveLightProxy(_ambientLightProxyHandle);
    _ambientLightProxyHandle = 0;

    _pSceneGraph = nullptr;
}

void SceneLightComponent::UpdateDirtyTransform(SceneGraph& SceneGraph)
{
    // No op (Directional light requires no expensive update so we just do it on the fly)
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------