// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ForwardRenderer.h"

#include "Buffers.h"
#include "RHI/RenderHardwareInterface.h"
#include "RenderCommandContext.h"
#include "RenderPipelineConstants.h"
#include "RenderQueue.h"
#include "RendererContext.h"
#include "Resources/GraphicsResourceManager.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void ost::ForwardRenderer::Initialize(const Vector2u& renderSize, RendererContext&& context)
{
    // Apply config and members
    _currentRenderSize = renderSize.VectorCast<Float32>();

    // Build resources
    context.rhi.CreateDepthStencilTexture(renderSize, false, _depthStencil);
    _depthStencil.SetDebugName("fwd_depthStencil");
}

// ------------------------------------------------------------

void ost::ForwardRenderer::Resize(const Vector2u& newSize, RendererContext&& context)
{
    _currentRenderSize = newSize.VectorCast<Float32>();
    context.rhi.CreateDepthStencilTexture(newSize.VectorCast<Uint32>(), false, _depthStencil);
    _depthStencil.SetDebugName("fwd_depthStencil");
}

// ------------------------------------------------------------

Float32 ost::ForwardRenderer::GetAspectRatio() const
{
    return _currentRenderSize.X / _currentRenderSize.Y;
}

const Vector2f& ost::ForwardRenderer::GetDimensions() const
{
    return _currentRenderSize;
}

// ------------------------------------------------------------

void ost::ForwardRenderer::ExecuteCommands(const IRenderQueue& queueInterface, RendererContext&& context)
{
    const EPipelineStage_ FullPipeline = EPipelineStage_VS | EPipelineStage_PS;

    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    const RenderHardwareInterface& rhi = context.rhi;

    // Clear and set targets
    rhi.ClearRenderTarget(_color);
    rhi.ClearDepthStencil(_depthStencil);
    rhi.SetRenderTarget(_color, &_depthStencil);

    rhi.SetBuffer(context.frameBuffer, PipelineConstant::Get(EBufferSlot::FrameBuffer), FullPipeline);
    rhi.SetBuffer(context.lightBuffer, PipelineConstant::Get(EBufferSlot::LightBuffer), FullPipeline);

    // Iterate all actual draw commands and draw them
    const Mesh* currentMesh = nullptr;
    const Material* currentMaterial = nullptr;
    const MaterialInstance* currentMaterialInstance = nullptr;

    RenderCommandContext ctx(rhi, context.resources);
    for (const RenderCommand& cmd : queue.GetDrawCommands())
    {
        cmd.Execute(ctx, context.objectBuffer);
    }

    rhi.Present();
}

const ITexture* ost::ForwardRenderer::GetOutputTarget(ERenderOutputTexture outputTarget) const
{
    switch (outputTarget)
    {
    case ERenderOutputTexture::Output:
        return &_color;
    case ERenderOutputTexture::Depth:
        return &_depthStencil;
    }

    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------