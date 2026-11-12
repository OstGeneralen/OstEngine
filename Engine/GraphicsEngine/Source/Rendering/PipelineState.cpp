// Kasper "OstGeneralen" Esbjornsson - 2026
#include "PipelineState.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderResourceLibrary.h"

#include <Utility/Hash.h>

using namespace ost;

// ------------------------------------------------------------

PipelineState::PipelineState()
    : topology{EPrimitiveTopology::TriangleList}
    , blendMode{EBlendMode::Unknown}
    , depthMode{EDepthMode::Unknown}
    , vertexShader{}
    , pixelShader{}
{
}

// ------------------------------------------------------------

void ost::PipelineState::Apply(const RenderHardwareInterface& rhi)
{
    rhi.SetPrimitiveTopology(topology);

    if (blendMode != EBlendMode::Unknown)
    {
        rhi.SetBlendState(RenderResourceLibrary::Get().GetBlendState(blendMode));
    }
    if (depthMode != EDepthMode::Unknown)
    {
        rhi.SetDepthStencilState(RenderResourceLibrary::Get().GetDepthStencilState(depthMode));
    }

    if (vertexShader)
    {
        rhi.SetShader(vertexShader, EPipelineStage::VS);
    }
    if (pixelShader)
    {
        rhi.SetShader(pixelShader, EPipelineStage::PS);
    }

    rhi.SetRenderTargets(targets, numTargets, (depthTarget ? &depthTarget : nullptr));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------