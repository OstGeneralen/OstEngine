// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DeferredRenderer.h"

#include "Buffers.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "Materials/MaterialCompiler.h"
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"
#include "RenderCommandContext.h"
#include "RenderQueue.h"
#include "RendererContext.h"
#include "Resources/GraphicsResourceManager.h"
#include "Resources/ShaderCompiler.h"

using namespace ost;

// ------------------------------------------------------------

GBuffer::GBuffer() = default;
GBuffer::GBuffer(const GBuffer&) = default;
GBuffer::~GBuffer() = default;

// ------------------------------------------------------------

DeferredRenderer::DeferredRenderer() = default;
DeferredRenderer::~DeferredRenderer() = default;

// ------------------------------------------------------------

void DeferredRenderer::Initialize(const Vector2u& renderSize, RendererContext&& context)
{
    const auto& rhi = context.rhi;

    rhi.CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("DeferredFrameBuffer");

    rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("DeferredObjectBuffer");

    rhi.CreateBuffer(sizeof(LightsBufferStructure), _lightBuffer);
    _lightBuffer.SetDebugName("DeferredLightBuffer");

    // Treat initialization as a first "resize"
    Resize(renderSize, std::move(context));

    // Create The blit mesh
    _fullscreenMesh.indexOffset = 0;
    _fullscreenMesh.indexCount = 6;
    _fullscreenMesh.vertexOffset = 0;
    _fullscreenMesh.vertexCount = 4;

    FullscreenVertex tl = {{-1, 1, 1, 1}, {0, 0}};
    FullscreenVertex tr = {{1, 1, 1, 1}, {1, 0}};
    FullscreenVertex br = {{1, -1, 1, 1}, {1, 1}};
    FullscreenVertex bl = {{-1, -1, 1, 1}, {0, 1}};

    FullscreenVertex vertices[4] = {tl, tr, bl, br};
    Uint32 indices[6] = {0, 1, 2, 2, 1, 3};
    rhi.CreateVertexBuffer(sizeof(FullscreenVertex), 4, vertices, _fullscreenMesh.vertexBuffer);
    rhi.CreateIndexBuffer(6, indices, _fullscreenMesh.indexBuffer);

    // Todo: Unhackify this glorious mess of a pretend material
    MaterialDesc desc = {};
    desc.domain = EMaterialDomain::Fullscreen;
    desc.materialShaderPath = "Engine/Shader/Material/MaterialShader_DeferredLightFullscreen.hlsl";
    MaterialCompiler compiler(desc);
    compiler.Compile();
    rhi.CreatePSO(compiler.GetCompiledPSODescForward(), _fullscreenPSO);
}

// ------------------------------------------------------------

void ost::DeferredRenderer::Resize(const Vector2u& newSize, RendererContext&& context)
{
    _currentSize = newSize.VectorCast<Float32>();

    const RenderHardwareInterface& rhi = context.rhi;

    // Reset the GBuffer
    _gBuffer = {};

    // Create the G Buffer Textures
    rhi.CreateRenderTargetTexture(newSize, EDataFormat::RGBA_Unorm8, true, _gBuffer.albedo);
    rhi.CreateRenderTargetTexture(newSize, EDataFormat::RGBA_Unorm8, true, _gBuffer.normals);
    rhi.CreateRenderTargetTexture(newSize, EDataFormat::RGBA_Unorm8, true, _gBuffer.orm);
    rhi.CreateDepthStencilTexture(newSize, true, _gBuffer.depth);
}

// ------------------------------------------------------------

Float32 ost::DeferredRenderer::GetAspectRatio() const
{
    return _currentSize.X / _currentSize.Y;
}

const Vector2f& ost::DeferredRenderer::GetDimensions() const
{
    return _currentSize;
}

// ------------------------------------------------------------

void ost::DeferredRenderer::ExecuteCommands(const IRenderQueue& queueInterface, RendererContext&& context)
{
    const auto& rhi = context.rhi;
    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    // Execute the queue onto our gBuffer like normal

    // 1. Clear all render targets
    rhi.ClearRenderTarget(_gBuffer.albedo);
    rhi.ClearRenderTarget(_gBuffer.normals);
    rhi.ClearRenderTarget(_gBuffer.orm);
    rhi.ClearDepthStencil(_gBuffer.depth);

    // 2. Update and set the frame buffer
    FrameBufferStructure fb = {};
    fb.viewProjection = queue.GetView().viewProjection;
    fb.inverseViewProjection = queue.GetView().viewProjection.GetInverse();
    fb.inverseView = queue.GetView().viewInverse;
    fb.viewLocation = queue.GetView().viewInverse.ExtractTranslation();
    fb.WriteAndSetBuffer(_frameBuffer, rhi);

    // 3. Bind the color pass targets
    Texture colorTargets[3] = {_gBuffer.albedo, _gBuffer.normals, _gBuffer.orm};
    rhi.SetRenderTargets(colorTargets, 3, &_gBuffer.depth);

    // 4. Execute the color pass
    RenderCommandContext ctx(rhi, context.resources);
    for (const auto& cmd : queue.GetDrawCommands())
    {
        cmd.ExecuteDeferred(ctx, _objectBuffer);
    }

    // 5. Bind the fullscreen mesh
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures(EPipelineStage_PS);

    rhi.ClearRenderTarget(context.backbuffer);
    rhi.SetRenderTarget(context.backbuffer, nullptr);

    rhi.SetPSO(_fullscreenPSO);

    rhi.SetTexture(_gBuffer.albedo, 0, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.normals, 1, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.orm, 2, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.depth, 3, ost::EPipelineStage_PS);

    LightsBufferStructure lightsData = {};
    for (const LightCommand& cmd : queue.GetLightCommands())
    {
        if (cmd.type == LightCommand::EType::Directional)
        {
            lightsData.directional.color = cmd.color;
            lightsData.directional.direction = Vector4f(cmd.forward, 0);
        }
        if (cmd.type == LightCommand::EType::Ambient)
        {
            lightsData.ambient.color = cmd.color;
        }
    }
    lightsData.WriteAndSetBuffer(_lightBuffer, rhi);

    fb.WriteAndSetBuffer(_frameBuffer, rhi);

    rhi.Draw(_fullscreenMesh, true);

    rhi.UnsetTextures(EPipelineStage_PS | EPipelineStage_VS);
    rhi.UnsetRenderTargets();

    rhi.Present();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------