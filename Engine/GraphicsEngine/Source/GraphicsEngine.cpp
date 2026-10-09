// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
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

    Log::Log(GraphicsEngineLog, "Started Graphics Engine with Render Size: {}x{}", settings.output.renderSize.X, settings.output.renderSize.Y);

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
    _rhi.Initialize(GetRenderSize().VectorCast<Uint32>(), settings.output.nativeWindowHandle);
    _resourceManager.Initialize(_rhi);

    switch (settings.renderer.rendererType)
    {
    case ERendererType::Forward: {
        auto fwdRenderer = Ptr::NewUnique<ForwardRenderer>();
        fwdRenderer->Initialize(GetRenderSize().VectorCast<Float32>(), _rhi);
        _activeRenderer = std::move(fwdRenderer);
        break;
    }
    }
}

void GraphicsEngine::Shutdown()
{
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
        _activeRenderer->Resize(newRenderSize.VectorCast<Float32>());
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

void ost::GraphicsEngine::ExecuteAndClearCommandQueue()
{
    _activeRenderer->ExecuteCommands(_renderQueue.GetView(), _renderQueue);
    _renderQueue.Clear();
}

// ------------------------------------------------------------

Vector2f GraphicsEngine::GetRenderSize() const
{
    const Vector2f clientSize = _activeSettings.output.clientSize.VectorCast<Float32>();
    const Vector2f renderDimensions = {clientSize.X * _activeSettings.output.renderSize.X, clientSize.Y * _activeSettings.output.renderSize.Y};
    return renderDimensions;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------