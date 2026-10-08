// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/RenderGraph.h"

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    class CameraComponent : public RenderComponent
    {
    public:
        void MakeOrthographic(Float32 sizeFactorX, Float32 sizeFactorY);
        void MakePerspective(Float32 vFoV);

    public: // RenderComponent
        void InitializeRenderState(RenderGraph& renderGraph) override;
        void DestroyRenderState(RenderGraph& renderGraph) override;
        void UpdateDirtyTransform(RenderGraph& renderGraph) override;

    public:
        void ProcessTransformChanged();

    private:
        RenderGraph* _pRenderGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------