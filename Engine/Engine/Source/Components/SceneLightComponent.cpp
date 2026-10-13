// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/SceneLightComponent.h"

using namespace ost;

// ------------------------------------------------------------

void ost::SceneLightComponent::SetAmbientColor(const Color& color)
{
    if (_pSceneGraph)
    {
        _pSceneGraph->GetLightProxy(_ambientLightProxyHandle).color = color;
    }
}


// ------------------------------------------------------------

void SceneLightComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    _pSceneGraph = &SceneGraph;

    LightRenderProxy ambProxy;
    ambProxy.color = Colors::Black;
    ambProxy.type = ELightProxyType::Ambient;
    _ambientLightProxyHandle = SceneGraph.AddLightProxy(ambProxy);
}

void SceneLightComponent::DestroyRenderState(SceneGraph& SceneGraph)
{
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