// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/SceneProxies.h"

#include <Container/List.h>
#include <Container/SlotMap.h>
#include <GraphicsEngine/Rendering/Lights.h>
#include <Math/Color.h>
#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderComponent;

    class SceneGraph
    {
    public:
        ProxyHandle AddStaticMeshProxy(const StaticMeshRenderProxy& proxy);
        StaticMeshRenderProxy& GetStaticMeshProxy(ProxyHandle handle);
        void RemoveStaticMeshProxy(ProxyHandle handle);

        ProxyHandle AddLightProxy(const LightRenderProxy& proxy);
        LightRenderProxy& GetLightProxy(ProxyHandle handle);
        void RemoveLightProxy(ProxyHandle handle);

        ViewRenderProxy& GetViewProxy();

        const ViewRenderProxy& GetViewProxy() const;
        const List<StaticMeshRenderProxy>& GetStaticMeshProxies() const;
        const List<LightRenderProxy>& GetLightProxies() const;

        void MarkTransformDirty(RenderComponent& renderComponent);
        void ReconcileTransforms();

    private:
        ViewRenderProxy _viewProxy;
        SlotMap<StaticMeshRenderProxy> _meshProxies;
        SlotMap<LightRenderProxy> _lightProxies;

        List<RenderComponent*> _pendingTransformReevaluations;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------