// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/RenderGraph.h"

#include <Math/Color.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneLightComponent : public RenderComponent
    {
    public:
        void SetSunDirection(const Vector3f& direction);
        void SetAmbientColor(const Color& color);

    public: // RenderComponent
        void InitializeRenderState(RenderGraph& renderGraph) override;
        void DestroyRenderState(RenderGraph& renderGraph) override;
        void UpdateDirtyTransform(RenderGraph& renderGraph) override;

    private:
        Vector3f _sunDirection = Vector3f{0.0f, -1.0f, 0.0f};
        Color _ambientColor = Color{0.0f, 0.05f, 0.09f, 1.0f};

        ProxyHandle _directionalLightProxyHandle;
        ProxyHandle _ambientLightProxyHandle;

        RenderGraph* _pRenderGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------