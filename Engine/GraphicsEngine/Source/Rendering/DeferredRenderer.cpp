// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DeferredRenderer.h"

#include "Buffers.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "Materials/MaterialCompiler.h"
#include "Objects/RenderDefaultsLibrary.h"
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

    // Treat initialization as a first "resize"
    Resize(renderSize, std::move(context));

    // Todo: Unhackify this glorious mess of a pretend material
    MaterialDesc desc = {};
    desc.domain = EMaterialDomain::Fullscreen;
    desc.materialShaderPath = "Engine/Shader/Material/MaterialShader_FullscreenBlit.hlsl";
    desc.blending = EBlendState::Additive;

    MaterialCompiler compiler(desc);
    compiler.Compile();
    rhi.CreatePSO(compiler.GetCompiledPSODescForward(), _fullscreenPSO);

    // Deferred uses its own light buffer since it actually allows more lights to be drawn than the fixed count of 8
    rhi.CreateBuffer(sizeof(LightsBufferStructure), _lightBuffer);
    _lightBuffer.SetDebugName("Deferred_LightBuffer");
}

// ------------------------------------------------------------

void ost::DeferredRenderer::Resize(const Vector2u& newSize, RendererContext&& context)
{
    _currentSize = newSize.VectorCast<Float32>();

    const RenderHardwareInterface& rhi = context.rhi;

    // Reset the GBuffer + output texture
    _outputTexture = {};
    _gBuffer = {};

    // Create the output texture
    rhi.CreateRenderTargetTexture(newSize, EDataFormat::RGBA_Unorm8, true, _outputTexture);
    _outputTexture.SetDebugName("Deferred_Final");

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
    const EPipelineStage_ FullPipeline = EPipelineStage_VS | EPipelineStage_PS;

    const auto& rhi = context.rhi;
    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    rhi.SetViewport({0, 0}, _currentSize);

    // Execute the queue onto our gBuffer like normal
    rhi.SetBuffer(context.frameBuffer, PipelineConstant::Get(EBufferSlot::FrameBuffer), FullPipeline);

    // 1. Clear all render targets
    rhi.ClearRenderTarget(_gBuffer.albedo);
    rhi.ClearRenderTarget(_gBuffer.normals);
    rhi.ClearRenderTarget(_gBuffer.orm);
    rhi.ClearDepthStencil(_gBuffer.depth);

    // 2. Bind the color pass targets
    Texture colorTargets[3] = {_gBuffer.albedo, _gBuffer.normals, _gBuffer.orm};
    rhi.SetRenderTargets(colorTargets, 3, &_gBuffer.depth);

    // 3. Execute the color pass
    RenderCommandContext ctx(rhi, context.resources);
    for (const auto& cmd : queue.GetDrawCommands())
    {
        cmd.ExecuteDeferred(ctx, context.objectBuffer);
    }

    // 4. Light Pass
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures();

    rhi.SetPSO(_fullscreenPSO);

    rhi.ClearRenderTarget(_outputTexture);
    rhi.SetRenderTarget(_outputTexture, nullptr);

    rhi.SetTexture(_gBuffer.albedo, 0, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.normals, 1, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.orm, 2, ost::EPipelineStage_PS);
    rhi.SetTexture(_gBuffer.depth, 3, ost::EPipelineStage_PS);

    rhi.SetBuffersForIndexed(RenderDefaultsLibrary::GetBlitMesh().vertexBuffer, sizeof(FullscreenVertex), RenderDefaultsLibrary::GetBlitMesh().indexBuffer);

    // Go through the lights and keep drawing :)
    LightsBufferStructure lightData;
    SizeType lightIndex = 0;
    for (const auto& lightCommand : queue.GetLightCommands())
    {
        if (lightIndex == 8)
        {
            lightIndex = 0;
            lightData.numLights = 8;
            rhi.UpdateBuffer(_lightBuffer, &lightData, sizeof(LightsBufferStructure));
            rhi.SetBuffer(_lightBuffer, PipelineConstant::Get(EBufferSlot::LightBuffer), EPipelineStage_PS);
            rhi.Draw(6, 0, 0);
        }

        auto& renderLight = lightData.lights[lightIndex];
        renderLight.FromLightData(lightCommand.cmdData);

        lightIndex++;
    }

    if (lightIndex > 0)
    {
        lightData.numLights = static_cast<Uint32>(lightIndex);
        rhi.UpdateBuffer(_lightBuffer, &lightData, sizeof(LightsBufferStructure));
        rhi.SetBuffer(_lightBuffer, PipelineConstant::Get(EBufferSlot::LightBuffer), EPipelineStage_PS);
    }

    rhi.Draw(6, 0, 0);
}

const ITexture* ost::DeferredRenderer::GetOutputTarget(ERenderOutputTexture target) const
{
    switch (target)
    {
    case ERenderOutputTexture::Output:
        return &_outputTexture;
        break;
    case ERenderOutputTexture::Depth:
        return &_gBuffer.depth;
        break;
    case ERenderOutputTexture::GBufferAlbedo:
        return &_gBuffer.albedo;
        break;
    case ERenderOutputTexture::GBufferNormal:
        return &_gBuffer.normals;
        break;
    case ERenderOutputTexture::GBufferORM:
        return &_gBuffer.orm;
        break;
    }

    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------