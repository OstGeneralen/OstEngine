// Kasper "OstGeneralen" Esbjornsson - 2026
#include "World/SceneGraph.h"

#include "Engine/World/Component.h"

#include <GraphicsEngine/Rendering/IRenderScene.h>
#include <GraphicsEngine/Rendering/IRenderer.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

ProxyHandle SceneGraph::AddStaticMeshProxy(const StaticMeshRenderProxy& proxy)
{
    return _meshProxies.Add(proxy);
}

StaticMeshRenderProxy& SceneGraph::GetStaticMeshProxy(ProxyHandle handle)
{
    return _meshProxies[handle];
}

void SceneGraph::RemoveStaticMeshProxy(ProxyHandle handle)
{
    _meshProxies.Remove(handle);
}

// ------------------------------------------------------------

ProxyHandle SceneGraph::AddLightProxy(const LightRenderProxy& proxy)
{
    return _lightProxies.Add(proxy);
}

LightRenderProxy& SceneGraph::GetLightProxy(ProxyHandle handle)
{
    return _lightProxies[handle];
}

void SceneGraph::RemoveLightProxy(ProxyHandle handle)
{
    _lightProxies.Remove(handle);
}

// ------------------------------------------------------------

ViewRenderProxy& SceneGraph::GetViewProxy()
{
    return _viewProxy;
}

// ------------------------------------------------------------

const ViewRenderProxy& SceneGraph::GetViewProxy() const
{
    return _viewProxy;
}

// ------------------------------------------------------------

void SceneGraph::MarkTransformDirty(RenderComponent& renderComponent)
{
    _pendingTransformReevaluations.Add(&renderComponent);
}

void SceneGraph::ReconcileTransforms()
{
    for (auto rc : _pendingTransformReevaluations)
    {
        rc->UpdateDirtyTransform(*this);
    }

    _pendingTransformReevaluations.Clear();
}

// ------------------------------------------------------------

void ost::SceneGraph::PopulateRenderScene(IRenderScene& renderScene) const
{
    for (const auto& meshProxy : _meshProxies)
    {
        RenderSceneObject rso;
        rso.indexBuffer = meshProxy.indexBuffer;
        rso.vertexBuffer = meshProxy.vertexBuffer;
        rso.vertexShader = meshProxy.vertexShader;
        rso.pixelShader = meshProxy.pixelShader;
        rso.indexCount = meshProxy.indexCount;
        rso.indexOffset = meshProxy.indexOffset;
        rso.vertexCount = meshProxy.vertexCount;
        rso.transform = meshProxy.transform;
        renderScene.AddObject(rso);
    }

    for (const auto& lightProxy : _lightProxies)
    {
        RenderSceneLight rsl;
        rsl.data = lightProxy.proxyData;
        renderScene.AddLight(rsl);
    }

    RenderSceneCamera rsc;
    rsc.transform = _viewProxy.transform;
    switch (_viewProxy.projectionType)
    {
    case ViewRenderProxy::EProjectionType::Perspective: {
        rsc.projectionType = ERenderSceneCameraProjection::Persp;
        rsc.yFoV = _viewProxy.lValue;
        break;
    }
    case ViewRenderProxy::EProjectionType::Orthographic: {
        rsc.projectionType = ERenderSceneCameraProjection::Ortho;
        rsc.sizeFactors = {_viewProxy.lValue, _viewProxy.rValue};
        break;
    }
    }

    renderScene.SetCamera(rsc);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------