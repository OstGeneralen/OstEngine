// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

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

UniquePtr<IGraphicsEngine> IGraphicsEngine::CreateNew(const GraphicsEngineSettings& settings)
{
    auto ptr = Ptr::NewUnique<GraphicsEngine>();
    ptr->Initialize(settings);

    return ptr;
}

// ------------------------------------------------------------

GraphicsEngine::GraphicsEngine()
    : _activeSettings{}
    , _activeRenderer{}
    , _rhi{}
    , _resourceManager{}
    , _renderQueue{_resourceManager}
{
}

GraphicsEngine::~GraphicsEngine()
{
}

// ------------------------------------------------------------

bool GraphicsEngine::IsInitialized() const
{
    return _activeRenderer.IsValid();
}

void GraphicsEngine::Initialize(const GraphicsEngineSettings& settings)
{
    _activeSettings = settings;
    _rhi.Initialize(GetRenderSize().VectorCast<Uint32>(), settings.output.nativeWindowHandle, settings.output.fullscreen);
    _resourceManager.Initialize(_rhi);

    switch (settings.renderer.rendererType)
    {
    case ERendererType::Forward: {
        _activeRenderer = Ptr::NewUnique<ForwardRenderer>();
        break;
    }
    case ERendererType::Deferred: {
        _activeRenderer = Ptr::NewUnique<DeferredRenderer>();
        break;
    }
    }

    _activeRenderer->Initialize(GetRenderSize().VectorCast<Uint32>(), BuildRendererContext());

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

    _rhi.CreateBuffer(sizeof(LightsBufferStructure), _lightBuffer);
    _lightBuffer.SetDebugName("Buffer_Light");

    _rhi.CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("Buffer_Object");

    _rhi.CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("Buffer_Frame");
}

void GraphicsEngine::Shutdown()
{
    _samplers.Clear();
    _rhi = RenderHardwareInterface{};
}

void GraphicsEngine::UpdateSettings(const GraphicsEngineSettings& newSettings)
{
    OST_ASSERT(IsInitialized(), "Update Settings requires a correctly initialized RHI");

    // Cache the active window handle as this will not be allowed to be changed
    // Changing this requires a full restart of the Graphics Engine
    void* const windowHandle = _activeSettings.output.nativeWindowHandle;
    // Same for renderer type
    ERendererType rendererType = _activeSettings.renderer.rendererType;

    const Vector2u newRenderSize = ::CalculateRenderSize(newSettings.output.clientSize, newSettings.output.renderSize);
    const Vector2u oldRenderSize = ::CalculateRenderSize(_activeSettings.output.clientSize, _activeSettings.output.renderSize);

    if (newRenderSize != oldRenderSize)
    {
        _rhi.ResizeBackbuffer(newRenderSize, _backbuffer);
        _activeRenderer->Resize(newRenderSize, BuildRendererContext());
    }

    _activeSettings = newSettings;
    _activeSettings.output.nativeWindowHandle = windowHandle; // Restore with cached
    _activeSettings.renderer.rendererType = rendererType;
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

IGraphicsResourceManager& GraphicsEngine::GetResourceManager()
{
    return _resourceManager;
}

IMaterialManager& ost::GraphicsEngine::GetMaterialManager()
{
    return _resourceManager;
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
    // Not binding these at this point :)
    UpdateFrameBuffer();
    UpdateLightBuffer();

    // Execute commands under current renderer
    _activeRenderer->ExecuteCommands(_renderQueue, BuildRendererContext());
    _renderQueue.Clear();
}

const IRenderHardwareInterface& GraphicsEngine::GetRenderHardwareInterface() const
{
    return _rhi;
}

// ------------------------------------------------------------

RendererContext ost::GraphicsEngine::BuildRendererContext()
{
    return RendererContext(_rhi, _resourceManager, _backbuffer, _frameBuffer, _objectBuffer, _lightBuffer);
}
// ------------------------------------------------------------

Vector2f GraphicsEngine::GetRenderSize() const
{
    const Vector2f clientSize = _activeSettings.output.clientSize.VectorCast<Float32>();
    const Vector2f renderDimensions = {clientSize.X * _activeSettings.output.renderSize.X, clientSize.Y * _activeSettings.output.renderSize.Y};
    return renderDimensions;
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

void ost::GraphicsEngine::UpdateLightBuffer()
{
    Uint32 lightCount = 0;

    LightsBufferStructure bufferData = {};

    for (const auto& cmd : _renderQueue.GetLightCommands())
    {
        if(lightCount == 8)
        {
            break;
        }

        auto& thisLight = bufferData.lights[lightCount];
        thisLight.color = cmd.color;
        thisLight.position = cmd.position;
        thisLight.direction = cmd.forward;
        thisLight.radius = cmd.radius;

        switch (cmd.type)
        {
        case LightCommand::EType::Directional:
            thisLight.type = 0;
            break;
        case LightCommand::EType::Point:
            thisLight.type = 2;
            break;
        default:
            continue;
            break;
        }

        lightCount++;
    }

    bufferData.numLights = lightCount;

    _rhi.UpdateBuffer(_lightBuffer, &bufferData, sizeof(LightsBufferStructure));
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------