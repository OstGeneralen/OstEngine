// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Resources/GraphicsResourceManager.h"

#include <algorithm>

#include <Utility/Assert.h>

#include <d3d11_1.h>

using namespace ost;

// ------------------------------------------------------------

GraphicsEngine* GraphicsEngine::_pInstance = nullptr;

// ------------------------------------------------------------

namespace
{
    inline Vector2u CalculateRenderSize(const Vector2u& clientSize, const Vector2f& renderSize)
    {
        return Vector2u{static_cast<Uint32>(static_cast<Float32>(clientSize.X) * renderSize.X), static_cast<Uint32>(static_cast<Float32>(clientSize.Y) * renderSize.Y)};
    }
} // namespace

// ------------------------------------------------------------

GraphicsEngine& GraphicsEngine::GetInstance()
{
    return *_pInstance;
}

// ------------------------------------------------------------

GraphicsEngine::GraphicsEngine()
    : _activeSettings{}
    , _rhi{}
{
    OST_ASSERT(_pInstance == nullptr, "May only have one graphics engine instance per runtime");
    _pInstance = this;
}

GraphicsEngine::~GraphicsEngine()
{
    _rhi = nullptr;
    _pInstance = nullptr;
}

// ------------------------------------------------------------

void GraphicsEngine::Initialize(const GraphicsEngineSettings& settings)
{
    _rhi = Ptr::NewUnique<RenderHardwareInterface>();

    const Vector2u renderSize = ::CalculateRenderSize(settings.output.clientSize, settings.output.renderSize);
    if (_rhi->Initialize(renderSize, settings.output.nativeWindowHandle, _backbufferTexture) == false)
    {
        _rhi.Reset();
    }

    _rhi->CreateDepthStencilTexture(renderSize, false, _depthStencilTexture);

    _resourceManager = Ptr::NewUnique<GraphicsResourceManager>();
    _resourceManager->Initialize(*_rhi);

    _activeSettings = settings;
}

void GraphicsEngine::Shutdown()
{
    _rhi.Reset();
}

void GraphicsEngine::UpdateSettings(const GraphicsEngineSettings& newSettings)
{
    OST_ASSERT(_rhi.IsValid(), "Update Settings requires a correctly initialized RHI");

    // Cache the active window handle as this will not be allowed to be changed
    // Changing this requires a full restart of the Graphics Engine
    void* const windowHandle = _activeSettings.output.nativeWindowHandle;

    const Vector2u newRenderSize = ::CalculateRenderSize(newSettings.output.clientSize, newSettings.output.renderSize);
    const Vector2u oldRenderSize = ::CalculateRenderSize(_activeSettings.output.clientSize, _activeSettings.output.renderSize);

    if (newRenderSize != oldRenderSize)
    {
        _rhi->ResizeBackbuffer(newRenderSize, _backbufferTexture);
        _depthStencilTexture = {};
        _rhi->CreateDepthStencilTexture(newRenderSize, false, _depthStencilTexture);
    }

    _activeSettings = newSettings;
    _activeSettings.output.nativeWindowHandle = windowHandle; // Restore with cached
}

// ------------------------------------------------------------

void GraphicsEngine::Draw(const ModelHandle& modelHandle, const Matrix4x4& transform)
{
    const Model& model = _resourceManager->Get(modelHandle);

    for (const auto& submeshHandle : model.meshHandles)
    {
        const Mesh& mesh = _resourceManager->Get(submeshHandle);

        RenderCommand cmd;
        cmd.pMesh = &mesh;
        cmd.pMaterial = &_resourceManager->Get(model.materials[mesh.materialIndex]);
        cmd.transform = transform;

        _commands.Add(cmd);
    }
}

void ost::GraphicsEngine::DoRender(bool maintainCommandList)
{
    _rhi->ClearRenderTarget(_backbufferTexture, _activeSettings.renderer.clearColor);
    _rhi->ClearDepthStencil(_depthStencilTexture);

    // Sort by material and mesh
    //std::sort(_commands.begin(), _commands.end(), [](const RenderCommand& cmdA, const RenderCommand& cmdB) {
    //    const SizeType sortIndexA = (reinterpret_cast<SizeType>(cmdA.pMaterial) << 32) | (reinterpret_cast<SizeType>(cmdA.pMesh) & 0x00000000FFFFFFFF);
    //    const SizeType sortIndexB = (reinterpret_cast<SizeType>(cmdA.pMaterial) << 32) | (reinterpret_cast<SizeType>(cmdA.pMesh) & 0x00000000FFFFFFFF);
    //    return sortIndexA <=> sortIndexB;
    //});

    const Material* currentMaterial = nullptr;
    const Mesh* currentMesh = nullptr;

    for (const auto& cmd : _commands)
    {
        // Update Material if we're now drawing a different one
        if (cmd.pMaterial != currentMaterial)
        {
            currentMaterial = cmd.pMaterial;
            _rhi->SetPSO(currentMaterial->GetPSO());

            _rhi->UpdateBuffer(currentMaterial->GetVariablesBuffer(), currentMaterial->GetVariablesData(), currentMaterial->GetVariablesByteCount());
            _rhi->SetBuffer(currentMaterial->GetVariablesBuffer(), PipelineConstant::Get(EBufferSlot::MaterialProperties), EPipelineStage_VS | EPipelineStage_PS);

            
            for (SizeType textureIndex = 0; textureIndex < currentMaterial->GetTextureCount(); ++textureIndex)
            {
                _rhi->SetTexture(currentMaterial->GetTextures()[textureIndex], PipelineConstant::Get(ETextureSlot::Material0), EPipelineStage_VS | EPipelineStage_PS);
            }
        }

        // Update mesh if we're now drawing a different one
        if (cmd.pMesh != currentMesh)
        {
            _rhi->SetMeshBuffers(*cmd.pMesh);
        }

        _rhi->Draw(*cmd.pMesh);
    }

    if (!maintainCommandList)
    {
        _commands.Clear();
    }

    _rhi->Present();
}

// ------------------------------------------------------------

IGraphicsResourceManager& ost::GraphicsEngine::GetResourceManager()
{
    return *_resourceManager;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------