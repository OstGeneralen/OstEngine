// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/RenderGraph.h"

#include <GraphicsEngine/Objects/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class StaticMeshComponent : public RenderComponent
    {
    public:
        StaticMeshComponent( ModelHandle modelHandle );

    public: // Render Component
        void InitializeRenderState(RenderGraph& renderGraph) override;
        void DestroyRenderState(RenderGraph& renderGraph) override;
        void UpdateDirtyTransform(RenderGraph& renderGraph) override;

        void OnTransformMarkedDirty();
    private:
        RenderGraph* _pRenderGraph;
        ModelHandle _modelHandle;
        ProxyHandle _proxyMeshHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------