// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Resources/GraphicsResourceManager.h"
#include "Resources/ShaderCompiler.h"

#include <d3d11_1.h>

#include <algorithm>

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

namespace
{
    inline Vector2u CalculateRenderSize(const Vector2u& clientSize, const Vector2f& renderSize)
    {
        return Vector2u{static_cast<Uint32>(static_cast<Float32>(clientSize.X) * renderSize.X), static_cast<Uint32>(static_cast<Float32>(clientSize.Y) * renderSize.Y)};
    }
} // namespace

// ------------------------------------------------------------

GraphicsEngine::GraphicsEngine()
    : _activeSettings{}
    , _rhi{}
{
}

GraphicsEngine::~GraphicsEngine()
{
    _rhi = nullptr;
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

    _rhi->CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _rhi->CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);

    List<Uint8> vsBytecode = CompileShaderFromFile("EngineAssets/Shaders/TestShader.hlsl", EPipelineStage_VS);
    List<Uint8> psBytecode = CompileShaderFromFile("EngineAssets/Shaders/TestShader.hlsl", EPipelineStage_PS);

    PipelineStateObjectDesc psoDesc = {};
    psoDesc.pixelShader.bytecodeSize = psBytecode.GetSize();
    psoDesc.pixelShader.pBytecode = psBytecode.GetData();
    psoDesc.vertexShader.bytecodeSize = vsBytecode.GetSize();
    psoDesc.vertexShader.pBytecode = vsBytecode.GetData();

    psoDesc.primitiveTopology = EPrimitiveTopology::TriangleList;

    psoDesc.vertexLayout.Add(VertexElement{"POSITION", EDataSize::Float4});
    psoDesc.vertexLayout.Add(VertexElement{"NORMAL", EDataSize::Float3});
    psoDesc.vertexLayout.Add(VertexElement{"TANGENT", EDataSize::Float3});
    psoDesc.vertexLayout.Add(VertexElement{"COLOR", EDataSize::Float4});
    psoDesc.vertexLayout.Add(VertexElement{"TEXCOORD", EDataSize::Float2});

    _rhi->CreatePSO(psoDesc, _defaultPSO);
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

void GraphicsEngine::PushRenderCommand(const ModelHandle& modelHandle, const Matrix4x4& transform)
{
    const Model& model = _resourceManager->Get(modelHandle);

    for (const auto& submeshHandle : model.meshHandles)
    {
        const Mesh& mesh = _resourceManager->Get(submeshHandle);

        RenderCommand cmd;
        cmd.pMesh = &mesh;
        // cmd.pMaterial = &_resourceManager->Get(model.materials[mesh.materialIndex]);
        cmd.transform = transform;

        _commands.Add(cmd);
    }
}

void ost::GraphicsEngine::ExecuteRenderCommands(const Matrix4x4& view)
{
    _rhi->SetPSO(_defaultPSO);

    FrameBufferStructure frameBufferData;
    frameBufferData.viewMatrix = view;
    frameBufferData.inverseViewMatrix = view.GetInverse();
    _rhi->UpdateBuffer(_frameBuffer, &frameBufferData, sizeof(FrameBufferStructure));
    _rhi->SetBuffer(_frameBuffer, static_cast<Uint32>(EBufferSlot::FrameBuffer), EPipelineStage_PS | EPipelineStage_VS);

    _rhi->ClearRenderTarget(_backbufferTexture, _activeSettings.renderer.clearColor);
    _rhi->ClearDepthStencil(_depthStencilTexture);

    _rhi->SetRenderTarget(_backbufferTexture, &_depthStencilTexture);

    // Sort by material and mesh
    // std::sort(_commands.begin(), _commands.end(), [](const RenderCommand& cmdA, const RenderCommand& cmdB) {
    //    const SizeType sortIndexA = (reinterpret_cast<SizeType>(cmdA.pMaterial) << 32) | (reinterpret_cast<SizeType>(cmdA.pMesh) & 0x00000000FFFFFFFF);
    //    const SizeType sortIndexB = (reinterpret_cast<SizeType>(cmdA.pMaterial) << 32) | (reinterpret_cast<SizeType>(cmdA.pMesh) & 0x00000000FFFFFFFF);
    //    return sortIndexA <=> sortIndexB;
    //});

    const Material* currentMaterial = nullptr;
    const Mesh* currentMesh = nullptr;

    for (const auto& cmd : _commands)
    {
        // Update Material if we're now drawing a different one
        // if (cmd.pMaterial != currentMaterial)
        //{
        //    currentMaterial = cmd.pMaterial;
        //    _rhi->SetPSO(currentMaterial->GetPSO());
        //
        //    _rhi->UpdateBuffer(currentMaterial->GetVariablesBuffer(), currentMaterial->GetVariablesData(), currentMaterial->GetVariablesByteCount());
        //    _rhi->SetBuffer(currentMaterial->GetVariablesBuffer(), PipelineConstant::Get(EBufferSlot::MaterialProperties), EPipelineStage_VS | EPipelineStage_PS);
        //
        //
        //    for (SizeType textureIndex = 0; textureIndex < currentMaterial->GetTextureCount(); ++textureIndex)
        //    {
        //        _rhi->SetTexture(currentMaterial->GetTextures()[textureIndex], PipelineConstant::Get(ETextureSlot::Material0), EPipelineStage_VS | EPipelineStage_PS);
        //    }
        //}

        ObjectBufferStructure objectBufferData;
        objectBufferData.objectTransform = cmd.transform;
        _rhi->UpdateBuffer(_objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure));
        _rhi->SetBuffer(_objectBuffer, static_cast<Uint32>(EBufferSlot::ObjectBuffer), EPipelineStage_PS | EPipelineStage_VS);

        // Update mesh if we're now drawing a different one
        _rhi->Draw(*cmd.pMesh, cmd.pMesh != currentMesh);
        currentMesh = cmd.pMesh;
    }

    _rhi->Present();
}

void ost::GraphicsEngine::ClearRenderCommands()
{
    _commands.Clear();
}

// ------------------------------------------------------------

IGraphicsResourceManager& ost::GraphicsEngine::GetResourceManager()
{
    return *_resourceManager;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------