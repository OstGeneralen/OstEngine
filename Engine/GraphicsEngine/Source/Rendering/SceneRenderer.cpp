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

    _geometryPassPipelineState.topology = EPrimitiveTopology::TriangleList;
    _geometryPassPipelineState.blendMode = EBlendMode::Opaque;
    _geometryPassPipelineState.depthMode = EDepthMode::Less;
    _geometryPassPipelineState.numTargets = 3;

    _lightPassPipelineState.topology = EPrimitiveTopology::TriangleList;
    _lightPassPipelineState.blendMode = EBlendMode::Additive;
    _lightPassPipelineState.depthMode = EDepthMode::Disabled;
    _lightPassPipelineState.targets[0] = _outputTexture;

    InitializeTextures(rhi, renderDimensions);
}

void ost::SceneRenderer::Resize(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions)
{
    InitializeTextures(rhi, renderDimensions);
}

// ------------------------------------------------------------

void ost::SceneRenderer::ExecuteRenderScene(const RenderHardwareInterface& rhi)
{
    rhi.SetViewport({0, 0}, _outputTexture.GetSize().VectorCast<Float32>());

    rhi.UpdateBuffer(_frameBuffer, &_renderScene.GetFrameBufferData(), sizeof(FrameBufferStructure));
    rhi.SetBuffer(_frameBuffer, 10, EPipelineStage::All);

    // 1. Geometry Pass
    ExecuteGeometryPass(_renderScene, rhi);

    // 2. Intermediate Cleanup
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures();

    // 3. Lighting Pass
    ExecuteLightPass(_renderScene, rhi);

    // 4. Post execution cleanup
    rhi.UnsetRenderTargets();
    rhi.UnsetTextures();
}

void ost::SceneRenderer::BlitOutputToTarget(const Texture& target, const RenderHardwareInterface& rhi)
{
    rhi.SetViewport({0, 0}, target.GetSize().VectorCast<Float32>());

    const auto& blitMesh = RenderResourceLibrary::Get().GetBlitMesh();

    rhi.SetVertexBuffer(blitMesh.vertexBuffer, sizeof(BlitVertex));
    rhi.SetIndexBuffer(blitMesh.indexBuffer);
    rhi.SetShader(RenderResourceLibrary::Get().GetBlitVertexShader(), EPipelineStage::VS);
    rhi.SetShader(RenderResourceLibrary::Get().GetBlitPixelShader(), EPipelineStage::PS);
    rhi.SetRenderTarget(target, nullptr);
    rhi.SetTexture(_outputTexture, 0, EPipelineStage::PS);
    rhi.Draw(blitMesh.indexCount, 0, 0);
}

// ------------------------------------------------------------

IRenderScene& ost::SceneRenderer::GetRenderScene()
{
    return _renderScene;
}

const ITexture* ost::SceneRenderer::GetTargetTexture(ESceneRendererTargetTexture t) const
{
    switch (t)
    {
    case ESceneRendererTargetTexture::Albedo:
        return &_gbufferAlbedo;
    case ESceneRendererTargetTexture::Normal:
        return &_gbufferNormal;
    case ESceneRendererTargetTexture::ORM:
        return &_gbufferORM;
    case ESceneRendererTargetTexture::Depth:
        return &_gbufferDepth;
    case ESceneRendererTargetTexture::Output:
        return &_outputTexture;
    }
    return nullptr;
}

// ------------------------------------------------------------

void ost::SceneRenderer::ExecuteGeometryPass(const RenderScene& scene, const RenderHardwareInterface& rhi)
{
    rhi.ClearRenderTarget(_gbufferAlbedo);
    rhi.ClearRenderTarget(_gbufferNormal, {0.5f, 0.5f, 1.0f, 1.0f});
    rhi.ClearRenderTarget(_gbufferORM, {0.0f, 1.0f, 0.0f, 1.0f});
    rhi.ClearDepthStencil(_gbufferDepth, 1, 0);

    _geometryPassPipelineState.Apply(rhi);

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
            rhi.SetVertexBuffer(*cmd.pVertexBuffer, sizeof(StaticVertex));
            rhi.SetIndexBuffer(*cmd.pIndexBuffer);
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

    _lightPassPipelineState.Apply(rhi);

    rhi.SetTexture(_gbufferAlbedo, 0, EPipelineStage::PS);
    rhi.SetTexture(_gbufferNormal, 1, EPipelineStage::PS);
    rhi.SetTexture(_gbufferORM, 2, EPipelineStage::PS);
    rhi.SetTexture(_gbufferDepth, 3, EPipelineStage::PS);

    const auto& blitMesh = RenderResourceLibrary::Get().GetBlitMesh();
    rhi.SetVertexBuffer(blitMesh.vertexBuffer, sizeof(BlitVertex));
    rhi.SetIndexBuffer(blitMesh.indexBuffer);

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

    _geometryPassPipelineState.targets[0] = _gbufferAlbedo;
    _geometryPassPipelineState.targets[1] = _gbufferNormal;
    _geometryPassPipelineState.targets[2] = _gbufferORM;
    _geometryPassPipelineState.depthTarget = _gbufferDepth;

    _lightPassPipelineState.targets[0] = _outputTexture;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------