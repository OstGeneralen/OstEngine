// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneRenderer.h"

// Objects and Resources
#include "GraphicsEngine/Resources/ShaderCompiler.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderResourceLibrary.h"
#include "Rendering/RenderScene.h"

// RHI
#include "RHI/RenderHardwareInterface.h"

using namespace ost;

// ------------------------------------------------------------

ost::SceneRenderer::SceneRenderer()
{
}

void ost::SceneRenderer::InitializeResources(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions)
{
    // Buffers
    rhi.CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    rhi.CreateBuffer(sizeof(LightsBufferStructure), _lightBuffer);
    rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);

    InitializeTextures(rhi, renderDimensions);
}

void ost::SceneRenderer::Resize(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions)
{
    if (renderDimensions != _renderSize)
    {
        InitializeTextures(rhi, renderDimensions);
        _renderSize = renderDimensions;
    }
}

// ------------------------------------------------------------

void ost::SceneRenderer::ExecuteRenderScene(const RenderScene& scene, const RenderHardwareInterface& rhi)
{
    rhi.SetViewport({0, 0}, _renderSize.VectorCast<Float32>());

    rhi.UpdateBuffer(_frameBuffer, &scene.GetFrameBufferData(), sizeof(FrameBufferStructure));
    rhi.SetBuffer(_frameBuffer, 10, EPipelineStage::All);

    // 1. Geometry Pass
    ExecuteGeometryPass(scene, rhi);

    // 2. Intermediate Cleanup
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures();

    // 3. Lighting Pass
    ExecuteLightPass(scene, rhi);

    // 4. Post execution cleanup
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures();
}

void ost::SceneRenderer::BlitOutputToTarget(const Texture& target, const RenderHardwareInterface& rhi)
{
    rhi.SetViewport({0, 0}, target.GetSize().VectorCast<Float32>());

    const auto& blitMesh = RenderResourceLibrary::Get().GetBlitMesh();

    rhi.SetBuffersForIndexed(blitMesh.vertexBuffer, sizeof(BlitVertex), blitMesh.indexBuffer);
    rhi.SetShader(RenderResourceLibrary::Get().GetBlitVertexShader(), EPipelineStage::VS);
    rhi.SetShader(RenderResourceLibrary::Get().GetBlitPixelShader(), EPipelineStage::PS);
    rhi.SetRenderTarget(target, nullptr);
    rhi.SetTexture(_outputTexture, 0, EPipelineStage::PS);
    rhi.Draw(blitMesh.indexCount, 0, 0);
}

// ------------------------------------------------------------

void ost::SceneRenderer::ExecuteGeometryPass(const RenderScene& scene, const RenderHardwareInterface& rhi)
{

    rhi.ClearRenderTarget(_gbufferAlbedo);
    rhi.ClearRenderTarget(_gbufferNormal, {0.5f, 0.5f, 1.0f, 1.0f});
    rhi.ClearRenderTarget(_gbufferORM, {0.0f, 1.0f, 0.0f, 1.0f});
    rhi.ClearDepthStencil(_gbufferDepth, 1, 0);

    Texture gbufferTargets[3] = {_gbufferAlbedo, _gbufferNormal, _gbufferORM};
    rhi.SetRenderTargets(gbufferTargets, 3, &_gbufferDepth);

    rhi.SetBlendState(RenderResourceLibrary::Get().GetBlendState(EBlendState::Opaque));

    const Buffer* pCurrentIndexBuffer = nullptr;
    const Buffer* pCurrentVertexBuffer = nullptr;
    const Shader* pCurrentVertexShader = nullptr;
    const Shader* pCurrentPixelShader = nullptr;

    for (const RenderCommand& cmd : scene.GetRenderCommands())
    {
        if (pCurrentVertexShader != cmd.pVertexShader || pCurrentPixelShader != cmd.pPixelShader)
        {
            rhi.SetShader(*cmd.pVertexShader, EPipelineStage::VS);
            rhi.SetShader(*cmd.pPixelShader, EPipelineStage::PS);

            pCurrentVertexShader = cmd.pVertexShader;
            pCurrentPixelShader = cmd.pPixelShader;
        }

        if (pCurrentIndexBuffer != cmd.pIndexBuffer || pCurrentVertexBuffer != cmd.pVertexBuffer)
        {
            rhi.SetBuffersForIndexed(*cmd.pVertexBuffer, sizeof(StaticVertex), *cmd.pIndexBuffer);
            pCurrentIndexBuffer = cmd.pIndexBuffer;
            pCurrentVertexBuffer = cmd.pVertexBuffer;
        }

        ObjectBufferStructure objectBufferData;
        objectBufferData.objectTransform = cmd.transform;
        rhi.UpdateBuffer(_objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure));
        rhi.SetBuffer(_objectBuffer, 11, EPipelineStage::VS);

        rhi.Draw(cmd.indexCount, cmd.indexOffset, cmd.vertexOffset);
    }
}

void ost::SceneRenderer::ExecuteLightPass(const RenderScene& scene, const RenderHardwareInterface& rhi)
{

    rhi.ClearRenderTarget(_outputTexture);
    rhi.SetRenderTarget(_outputTexture, nullptr);

    rhi.SetTexture(_gbufferAlbedo, 0, EPipelineStage::PS);
    rhi.SetTexture(_gbufferNormal, 1, EPipelineStage::PS);
    rhi.SetTexture(_gbufferORM, 2, EPipelineStage::PS);
    rhi.SetTexture(_gbufferDepth, 3, EPipelineStage::PS);

    rhi.SetBlendState(RenderResourceLibrary::Get().GetBlendState(EBlendState::Additive));

    const auto& blitMesh = RenderResourceLibrary::Get().GetBlitMesh();
    rhi.SetBuffersForIndexed(blitMesh.vertexBuffer, sizeof(BlitVertex), blitMesh.indexBuffer);

    for (const auto& lightBufferData : scene.GetLightBuffersData())
    {
        rhi.UpdateBuffer(_lightBuffer, &lightBufferData, sizeof(LightsBufferStructure));
        rhi.SetBuffer(_lightBuffer, 12, EPipelineStage::PS);
        rhi.Draw(blitMesh.indexCount, 0, 0);
    }
}

// ------------------------------------------------------------

void ost::SceneRenderer::InitializeTextures(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions)
{
    rhi.CreateRenderTargetTexture(renderDimensions, EDataFormat::RGBA_Uint8, true, _gbufferAlbedo);
    rhi.CreateRenderTargetTexture(renderDimensions, EDataFormat::RGBA_Uint8, true, _gbufferNormal);
    rhi.CreateRenderTargetTexture(renderDimensions, EDataFormat::RGBA_Uint8, true, _gbufferORM);
    rhi.CreateDepthStencilTexture(renderDimensions, true, _gbufferDepth);
    rhi.CreateRenderTargetTexture(renderDimensions, EDataFormat::RGBA_Uint8, true, _outputTexture);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------