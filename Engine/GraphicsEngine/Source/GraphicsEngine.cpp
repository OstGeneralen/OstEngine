// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

#include "Objects/RenderDefaultsLibrary.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
#include "Rendering/DeferredRenderer.h"
#include "Rendering/ForwardRenderer.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Resources/GraphicsResourceManager.h"
#include "Resources/ShaderCompiler.h"

#include <d3d11_1.h>
#include <dxgi.h>

#include <OstLog.h>
#include <algorithm>

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

auto GraphicsEngineLog = Log::NewCategory("GraphicsEngine", Log::EVerbosity::Message);

// ------------------------------------------------------------

namespace
{
    inline Vector2u CalculateRenderSize(const Vector2u& clientSize, const Vector2f& renderSize)
    {
        return Vector2u{static_cast<Uint32>(static_cast<Float32>(clientSize.X) * renderSize.X), static_cast<Uint32>(static_cast<Float32>(clientSize.Y) * renderSize.Y)};
    }
} // namespace

// ------------------------------------------------------------

UniquePtr<IGraphicsEngine> IGraphicsEngine::Create(ServiceLocator& services, void* winHandle, const Vector2u& outputSize)
{
    auto ptr = Ptr::NewUnique<GraphicsEngine>(services, winHandle, outputSize);
    return ptr;
}

// ------------------------------------------------------------

GraphicsEngine::GraphicsEngine(ServiceLocator& serviceLocator, void* windowHandle, const Vector2u& outputSize)
    : _serviceLocator{serviceLocator}
    , _activeRenderer{}
    , _rhi{}
    , _resourceManager{}
    , _renderQueue{_resourceManager}
{
    // Create the RHI from the provided window information (force fullscreen false for now)
    _rhi.Initialize(outputSize, windowHandle, false);
    _resourceManager.Initialize(_rhi);

    RenderDefaultsLibrary::Initialize(_rhi);

    _activeRenderer = Ptr::NewUnique<DeferredRenderer>();
    _activeRenderer->Initialize(outputSize, BuildRendererContext());

    InitializeGlobalResources();

    // Register Globally Accessible Services
    _serviceLocator.RegisterUnmanaged<IGraphicsResourceManager>(&_resourceManager);
    _serviceLocator.RegisterUnmanaged<IMaterialManager>(&_resourceManager);
    _serviceLocator.RegisterUnmanaged<IRenderHardwareInterface>(&_rhi);
}

GraphicsEngine::~GraphicsEngine()
{
    _serviceLocator.Unregister<IGraphicsResourceManager>();
    _serviceLocator.Unregister<IMaterialManager>();
    _serviceLocator.Unregister<IRenderHardwareInterface>();
}

// ------------------------------------------------------------

bool GraphicsEngine::IsInitialized() const
{
    return _activeRenderer.IsValid();
}

void GraphicsEngine::Shutdown()
{
    _samplers.Clear();
    _rhi = RenderHardwareInterface{};
}

void ost::GraphicsEngine::SetRenderSize(const Vector2u& size)
{
    _activeRenderer->Resize(size, BuildRendererContext());
}

void ost::GraphicsEngine::SetOutputSize(const Vector2u& size)
{
    _rhi.ResizeBackbuffer(size, _backbuffer);
}

// ------------------------------------------------------------

IRenderer& GraphicsEngine::GetRenderer()
{
    return *_activeRenderer;
}

IRenderQueue& GraphicsEngine::GetRenderQueue()
{
    return _renderQueue;
}

void ost::GraphicsEngine::ExecuteAndClearCommandQueue()
{
    // Start by resetting bindings
    _rhi.UnsetRenderTargets();
    _rhi.UnsetTextures();

    // Always bind the samplers since these are globals
    _rhi.SetSampler(_samplers[ESamplerSlot::TrilinearWrap], PipelineConstant::Get(ESamplerSlot::TrilinearWrap));
    _rhi.SetSampler(_samplers[ESamplerSlot::TrilinearClamp], PipelineConstant::Get(ESamplerSlot::TrilinearClamp));
    _rhi.SetSampler(_samplers[ESamplerSlot::PointWrap], PipelineConstant::Get(ESamplerSlot::PointWrap));
    _rhi.SetSampler(_samplers[ESamplerSlot::PointClamp], PipelineConstant::Get(ESamplerSlot::PointClamp));

    // Update the buffers based on the command queue
    UpdateFrameBuffer();

    // Execute commands under current renderer
    _activeRenderer->ExecuteCommands(_renderQueue, BuildRendererContext());
    _renderQueue.Clear();
}

void ost::GraphicsEngine::DrawRendererOutput(ERenderOutputTexture presentOutputTexture)
{
    // Draw the output of the current renderer onto the backbuffer and then present
    _rhi.ClearRenderTarget(_backbuffer);
    _rhi.SetRenderTarget(_backbuffer);

    _rhi.SetTexture(*static_cast<const Texture*>(_activeRenderer->GetOutputTarget(presentOutputTexture)), 0, EPipelineStage_PS);

    _rhi.SetPSO(RenderDefaultsLibrary::GetBlitPSO());
    _rhi.SetBuffersForIndexed(RenderDefaultsLibrary::GetBlitMesh().vertexBuffer, sizeof(FullscreenVertex), RenderDefaultsLibrary::GetBlitMesh().indexBuffer);
    _rhi.Draw(RenderDefaultsLibrary::GetBlitMesh().indexCount, RenderDefaultsLibrary::GetBlitMesh().indexOffset, RenderDefaultsLibrary::GetBlitMesh().vertexOffset);
}

void ost::GraphicsEngine::Present()
{
    _rhi.Present();
}

// ------------------------------------------------------------

void ost::GraphicsEngine::InitializeGlobalResources()
{
    TextureSampler buildSampler;

    _rhi.CreateSampler(ESamplerAddressMode::Wrap, ESamplerType::Trilinear, buildSampler);
    _samplers.Insert(ESamplerSlot::TrilinearWrap, buildSampler);

    _rhi.CreateSampler(ESamplerAddressMode::Clamp, ESamplerType::Trilinear, buildSampler);
    _samplers.Insert(ESamplerSlot::TrilinearClamp, buildSampler);

    _rhi.CreateSampler(ESamplerAddressMode::Wrap, ESamplerType::Point, buildSampler);
    _samplers.Insert(ESamplerSlot::PointWrap, buildSampler);

    _rhi.CreateSampler(ESamplerAddressMode::Clamp, ESamplerType::Point, buildSampler);
    _samplers.Insert(ESamplerSlot::PointClamp, buildSampler);

    _rhi.CreateBackbuffer(_backbuffer);

    _rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("Buffer_Object");

    _rhi.CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("Buffer_Frame");
}

// ------------------------------------------------------------

RendererContext ost::GraphicsEngine::BuildRendererContext()
{
    return RendererContext(_rhi, _resourceManager, _frameBuffer, _objectBuffer);
}
// ------------------------------------------------------------


void ost::GraphicsEngine::UpdateFrameBuffer()
{
    FrameBufferStructure frameBufferData;
    frameBufferData.viewProjection = _renderQueue.GetView().viewProjection;
    frameBufferData.inverseViewProjection = _renderQueue.GetView().viewProjection.GetInverse();
    frameBufferData.inverseView = _renderQueue.GetView().viewInverse;
    frameBufferData.viewLocation = _renderQueue.GetView().viewInverse.ExtractTranslation();
    _rhi.UpdateBuffer(_frameBuffer, &frameBufferData, sizeof(FrameBufferStructure));
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------