// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneLightComponent.h"

using namespace ost;

// ------------------------------------------------------------

void ost::SceneLightComponent::SetSunDirection(const Vector3f& direction)
{
    _sunDirection = direction;
    if (_pRenderGraph)
    {
        _pRenderGraph->GetLightProxy(_directionalLightProxyHandle).direction = _sunDirection;
    }
}

void ost::SceneLightComponent::SetAmbientColor(const Color& color)
{
    _ambientColor = color;
    if (_pRenderGraph)
    {
        _pRenderGraph->GetLightProxy(_ambientLightProxyHandle).color = _ambientColor;
    }
}

// ------------------------------------------------------------

void SceneLightComponent::InitializeRenderState(RenderGraph& renderGraph)
{
    _pRenderGraph = &renderGraph;

    LightRenderProxy dirProxy;
    dirProxy.direction = _sunDirection;
    dirProxy.type = ELightProxyType::Directional;
    dirProxy.color = Colors::White;
    _directionalLightProxyHandle = renderGraph.AddLightProxy(dirProxy);

    LightRenderProxy ambProxy;
    ambProxy.color = _ambientColor;
    ambProxy.type = ELightProxyType::Ambient;
    _ambientLightProxyHandle = renderGraph.AddLightProxy(ambProxy);
}

void SceneLightComponent::DestroyRenderState(RenderGraph& renderGraph)
{
    renderGraph.RemoveLightProxy(_directionalLightProxyHandle);
    _directionalLightProxyHandle = 0;

    renderGraph.RemoveLightProxy(_ambientLightProxyHandle);
    _ambientLightProxyHandle = 0;

    _pRenderGraph = nullptr;
}

void SceneLightComponent::UpdateDirtyTransform(RenderGraph& renderGraph)
{
    // No op (Directional light requires no expensive update so we just do it on the fly)
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------