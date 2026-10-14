// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DeferredRenderer.h"

#include "Buffers.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"
#include "RenderQueue.h"
#include "RendererContext.h"
#include "Resources/GraphicsResourceManager.h"

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
    rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    rhi.CreateBuffer(sizeof(LightsBufferStructure), _lightBuffer);

    // Treat initialization as a first "resize"
    Resize(renderSize, std::move(context));

    // Create The blit mesh
    _fullscreenMesh.indexOffset = 0;
    _fullscreenMesh.indexCount = 6;
    _fullscreenMesh.vertexOffset = 0;
    _fullscreenMesh.vertexCount = 4;

    FullscreenVertex tl = {{-1, -1, 0, 1}, {0, 0}};
    FullscreenVertex tr = {{1, -1, 0, 1}, {1, 0}};
    FullscreenVertex br = {{1, 1, 0, 1}, {1, 1}};
    FullscreenVertex bl = {{-1, 1, 0, 1}, {0, 1}};

    FullscreenVertex vertices[4] = {tl, tr, bl, br};
    Uint32 indices[6] = {0, 1, 2, 2, 1, 3};
    rhi.CreateVertexBuffer(sizeof(FullscreenVertex), 4, vertices, _fullscreenMesh.vertexBuffer);
    rhi.CreateIndexBuffer(6, indices, _fullscreenMesh.indexBuffer);
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
    rhi.CreateRenderTargetTexture(newSize, EDataFormat::RGB_Float32, true, _gBuffer.pos);
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
    rhi.ClearRenderTarget(_gBuffer.pos);
    rhi.ClearDepthStencil(_gBuffer.depth);

    // 2. Update and set the frame buffer
    FrameBufferStructure fb = {};
    fb.viewProjection = queue.GetView().viewProjection;
    fb.inverseView = queue.GetView().viewInverse;
    fb.viewLocation = queue.GetView().viewInverse.ExtractTranslation();
    fb.WriteAndSetBuffer(_frameBuffer, rhi);

    // 3. Bind the color pass targets
    Texture colorTargets[4] = {_gBuffer.albedo, _gBuffer.normals, _gBuffer.orm, _gBuffer.pos};
    rhi.SetRenderTargets(colorTargets, 4, &_gBuffer.depth);

    // 4. Execute the color pass
    for (const auto& cmd : queue.GetDrawCommands())
    {
    }

    // 5. Bind the fullscreen mesh
    rhi.SetRenderTarget(context.backbuffer, nullptr);
    rhi.Draw(_fullscreenMesh, true);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------