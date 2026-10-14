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

    context.rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("fwd_objectBuffer");

    context.rhi.CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("fwd_frameBuffer");

    context.rhi.CreateBuffer(sizeof(LightsBufferStructure), _sceneLightBuffer);
    _sceneLightBuffer.SetDebugName("fwd_sceneLightBuffer");
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
    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    const RenderHardwareInterface& rhi = context.rhi;
    auto renderView = queue.GetView();

    // Clear and set targets
    rhi.ClearRenderTarget(context.backbuffer);
    rhi.ClearDepthStencil(_depthStencil);
    rhi.SetRenderTarget(context.backbuffer, &_depthStencil);

    // Update and upload frame buffer
    FrameBufferStructure frameBufferData = {};
    frameBufferData.viewProjection = renderView.viewProjection;
    frameBufferData.inverseView = renderView.viewInverse;
    frameBufferData.viewLocation = renderView.viewInverse.ExtractTranslation();
    frameBufferData.WriteAndSetBuffer(_frameBuffer, rhi);

    // Update and upload light buffer
    LightsBufferStructure lightsData = {};
    for (const LightCommand& cmd : queue.GetLightCommands())
    {
        if (cmd.type == LightCommand::EType::Directional)
        {
            lightsData.directional.color = cmd.color;
            lightsData.directional.direction = cmd.forward;
        }
        if (cmd.type == LightCommand::EType::Ambient)
        {
            lightsData.ambient.color = cmd.color;
        }
    }
    lightsData.WriteAndSetBuffer( _sceneLightBuffer, rhi );

    // Iterate all actual draw commands and draw them
    const Mesh* currentMesh = nullptr;
    const Material* currentMaterial = nullptr;
    const MaterialInstance* currentMaterialInstance = nullptr;

    RenderCommandContext ctx(rhi, context.resources);
    for (const RenderCommand& cmd : queue.GetDrawCommands())
    {
        cmd.Execute(ctx, _objectBuffer);
    }

    rhi.Present();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------