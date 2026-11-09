// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Objects/PipelineStateObject.h"

#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class PSOCache
    {
    public:
        PSOCache(const RenderHardwareInterface& rhi);

        // Generate the PSO if it doesn't exist in the cache already
        PipelineStateObject& GetPSO(const GraphicsState& gfxState);

    private:
        const RenderHardwareInterface& _rhi;

        Map<GraphicsState, PipelineStateObject> _cache;

        // Map of shared rhi data between pso's (i.e alpha blend blend state is always just alpha blend)
        Map<EVertexType, List<VertexElement>> _vertexLayouts;
        Map<EBlendState, ComPtr<RHIBlendState>> _blendStates;

        
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------