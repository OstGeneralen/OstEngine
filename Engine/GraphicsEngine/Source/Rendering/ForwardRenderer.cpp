// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ForwardRenderer.h"

#include "RHI/RenderHardwareInterface.h"
#include "RenderContext.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Rendering/RenderQueue.h"
#include "Resources/GraphicsResourceManager.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void ost::ForwardRenderer::Initialize(const Vector2f& renderSize, RenderHardwareInterface& rhi, GraphicsResourceManager& resources)
{
    // Apply config and members
    _rhi = &rhi;
    _resources = &resources;
    _currentRenderSize = renderSize;

    // Build resources
    _rhi->CreateBackbuffer(_backbuffer);
    _backbuffer.SetDebugName("fwd_backbuffer");

    _rhi->CreateDepthStencilTexture(renderSize.VectorCast<Uint32>(), false, _depthStencil);
    _depthStencil.SetDebugName("fwd_depthStencil");

    _rhi->CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("fwd_objectBuffer");

    _rhi->CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("fwd_frameBuffer");

    _rhi->CreateBuffer(sizeof(LightsBufferStructure), _sceneLightBuffer);
    _sceneLightBuffer.SetDebugName("fwd_sceneLightBuffer");
}

// ------------------------------------------------------------

void ost::ForwardRenderer::Resize(const Vector2f& newSize)
{
    _currentRenderSize = newSize;
    _rhi->ResizeBackbuffer(newSize.VectorCast<Uint32>(), _backbuffer);
    _rhi->CreateDepthStencilTexture(newSize.VectorCast<Uint32>(), false, _depthStencil);

    _backbuffer.SetDebugName("fwd_backBuffer");
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

void ost::ForwardRenderer::ExecuteCommands(const RenderView& renderView, const IRenderQueue& queueInterface)
{
    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    // Clear and set targets
    _rhi->ClearRenderTarget(_backbuffer);
    _rhi->ClearDepthStencil(_depthStencil);
    _rhi->SetRenderTarget(_backbuffer, &_depthStencil);

    // Update and upload frame buffer
    FrameBufferStructure frameBufferData = {};
    frameBufferData.viewProjection = renderView.viewProjection;
    frameBufferData.inverseView = renderView.viewInverse;
    frameBufferData.viewLocation = renderView.viewInverse.ExtractTranslation();
    _rhi->UpdateBuffer(_frameBuffer, &frameBufferData, sizeof(FrameBufferStructure));
    _rhi->SetBuffer(_frameBuffer, PipelineConstant::Get(EBufferSlot::FrameBuffer), EPipelineStage_VS | EPipelineStage_PS);

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
    _rhi->UpdateBuffer(_sceneLightBuffer, &lightsData, sizeof(LightsBufferStructure));
    _rhi->SetBuffer(_sceneLightBuffer, PipelineConstant::Get(EBufferSlot::LightBuffer), EPipelineStage_VS | EPipelineStage_PS);

    // Iterate all actual draw commands and draw them
    const Mesh* currentMesh = nullptr;
    const Material* currentMaterial = nullptr;
    const MaterialInstance* currentMaterialInstance = nullptr;

    RenderContext ctx(*_rhi, *_resources);
    for (const RenderCommand& cmd : queue.GetDrawCommands())
    {
        cmd.Execute(ctx, _objectBuffer);
    }

    _rhi->Present();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------