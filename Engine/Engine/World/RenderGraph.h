// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Container/SlotMap.h>
#include <GraphicsEngine/Objects/ObjectHandles.h>
#include <Math/Color.h>
#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderComponent;

    struct StaticMeshRenderProxy
    {
        ModelHandle hModel;
        Matrix4x4 transform;
    };

    enum class ELightProxyType
    {
        Directional,
        Ambient,
        // Only these two for now, extend the render proxy once we get to point and spot as well
    };

    struct LightRenderProxy
    {
        ELightProxyType type;
        Vector3f direction;
        Color color;
    };

    struct ViewRenderProxy
    {
        enum class EProjectionType
        {
            Perspective,
            Orthographic,
        } projectionType;

        Float32 lValue; // For Perspective, this is vFoV, for ortho this is percentage of width
        Float32 rValue; // For Perspective this is unused, for ortho this is percentage of height

        Matrix4x4 transform;
    };

    using ProxyHandle = Uint64;

    class RenderGraph
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