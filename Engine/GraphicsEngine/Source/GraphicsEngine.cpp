// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Resources/GraphicsResourceManager.h"

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
    , _rhi{}
    , _resourceManager{}
    , _globalResourceLibrary{}
    , _GraphicsScene{}
    , _sceneRenderer{}
{
    // Create the RHI from the provided window information (force fullscreen false for now)
    _rhi.Initialize(outputSize, windowHandle, false);
    _resourceManager.Initialize(_rhi);

    _globalResourceLibrary.InitializeResources(_rhi);
    _sceneRenderer.InitializeResources(_rhi, outputSize);

    _outputSize = outputSize.VectorCast<Float32>();

    // Register Globally Accessible Services
    _serviceLocator.RegisterUnmanaged<IGraphicsResourceManager>(&_resourceManager);
    _serviceLocator.RegisterUnmanaged<IRenderHardwareInterface>(&_rhi);
}

GraphicsEngine::~GraphicsEngine()
{
    _serviceLocator.Unregister<IGraphicsResourceManager>();
    _serviceLocator.Unregister<IRenderHardwareInterface>();
}

// ------------------------------------------------------------

bool GraphicsEngine::IsInitialized() const
{
    return true;
}

void GraphicsEngine::Shutdown()
{
    _samplers.Clear();
    _rhi = RenderHardwareInterface{};
}

void ost::GraphicsEngine::SetRenderSize(const Vector2u& size)
{
    if (size != _renderSize)
    {
        _sceneRenderer.Resize(_rhi, size);
        _renderSize = size;
    }
}

void ost::GraphicsEngine::SetOutputSize(const Vector2u& size)
{
    if (size != _outputSize)
    {
        _rhi.ResizeBackbuffer(size, _backbuffer);
        _outputSize = size;
    }
}

// ------------------------------------------------------------

IGraphicsScene& ost::GraphicsEngine::BeginGraphicsScene()
{
    _graphicsScene.Clear();
    return _graphicsScene;
}

void ost::GraphicsEngine::LockGraphicsScene()
{
    _graphicsScene.PrepareData(_resourceManager, _renderSize.VectorCast<Float32>());
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

void ost::GraphicsEngine::ClearAndSetBackbuffer()
{
    _rhi.ClearRenderTarget(_backbuffer);
    _rhi.SetRenderTarget(_backbuffer);
}

void ost::GraphicsEngine::DrawRendererOutput(ERenderOutputTexture presentOutputTexture)
{
    _rhi.SetViewport({0, 0}, _outputSize);

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
// ------------------------------------------------------------
// ------------------------------------------------------------