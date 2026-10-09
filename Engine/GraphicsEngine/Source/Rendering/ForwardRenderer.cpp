// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ForwardRenderer.h"

#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Rendering/RenderQueue.h"
#include "Resources/ShaderCompiler.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void ost::ForwardRenderer::Initialize(const Vector2f& renderSize, RenderHardwareInterface& rhi)
{
    // Apply config and members
    _rhi = &rhi;
    _currentRenderSize = renderSize;

    // Build resources
    _rhi->CreateBackbuffer(_backbuffer);
    _backbuffer.SetDebugName("fwd_backbuffer");

    _rhi->CreateDepthStencilTexture(renderSize.VectorCast<Uint32>(), false, _depthStencil);
    _depthStencil.SetDebugName("fwd_depthStencil");

    _rhi->CreateBuffer(sizeof(ObjectBufferStructure), _objectBuffer);
    _objectBuffer.SetDebugName("fwd_objectBuffer");

    _rhi->CreateBuffer(sizeof(FrameBufferStructure), _frameBuffer);
    _frameBuffer.SetDebugName("fwd_frameBuffer");

    _rhi->CreateBuffer(sizeof(LightsBufferStructure), _sceneLightBuffer);
    _sceneLightBuffer.SetDebugName("fwd_sceneLightBuffer");

    // Create the PSO
    List<Uint8> vertexShaderBytecode = CompileShaderFromFile("EngineAssets/Shaders/TestShader.hlsl", EPipelineStage_VS);
    List<Uint8> pixelShaderBytecode = CompileShaderFromFile("EngineAssets/Shaders/TestShader.hlsl", EPipelineStage_PS);

    PipelineStateObjectDesc defaultPSODesc = {};
    defaultPSODesc.primitiveTopology = EPrimitiveTopology::TriangleList;

    defaultPSODesc.vertexShader.bytecodeSize = vertexShaderBytecode.GetSize();
    defaultPSODesc.vertexShader.pBytecode = vertexShaderBytecode.GetData();

    defaultPSODesc.pixelShader.bytecodeSize = pixelShaderBytecode.GetSize();
    defaultPSODesc.pixelShader.pBytecode = pixelShaderBytecode.GetData();

    defaultPSODesc.vertexLayout.Add(VertexElement{"POSITION", EDataSize::Float4});
    defaultPSODesc.vertexLayout.Add(VertexElement{"NORMAL", EDataSize::Float3});
    defaultPSODesc.vertexLayout.Add(VertexElement{"TANGENT", EDataSize::Float3});
    defaultPSODesc.vertexLayout.Add(VertexElement{"COLOR", EDataSize::Float4});
    defaultPSODesc.vertexLayout.Add(VertexElement{"TEXCOORD", EDataSize::Float2});

    _rhi->CreatePSO(defaultPSODesc, _defaultPSO);
    _defaultPSO.SetDebugName("fwd_defaultPSO");
}

// ------------------------------------------------------------

void ost::ForwardRenderer::Resize(const Vector2f& newSize)
{
    _currentRenderSize = newSize;
    _rhi->ResizeBackbuffer(newSize.VectorCast<Uint32>(), _backbuffer);
    _rhi->CreateDepthStencilTexture(newSize.VectorCast<Uint32>(), false, _depthStencil);

    _backbuffer.SetDebugName("fwd_backBuffer");
    _depthStencil.SetDebugName("fwd_depthStencil");
}

// ------------------------------------------------------------

Float32 ost::ForwardRenderer::GetAspectRatio() const
{
    return _currentRenderSize.X / _currentRenderSize.Y;
}

const Vector2f& ost::ForwardRenderer::GetDimensions() const
{
    return _currentRenderSize;
}

// ------------------------------------------------------------

void ost::ForwardRenderer::ExecuteCommands(const Matrix4x4& view, const IRenderQueue& queueInterface)
{
    const RenderQueue& queue = static_cast<const RenderQueue&>(queueInterface);

    _rhi->SetPSO(_defaultPSO);

    // Clear and set targets
    _rhi->ClearRenderTarget(_backbuffer);
    _rhi->ClearDepthStencil(_depthStencil);
    _rhi->SetRenderTarget(_backbuffer, &_depthStencil);

    // Update and upload frame buffer
    FrameBufferStructure frameBufferData = {};
    frameBufferData.viewMatrix = view;
    frameBufferData.inverseViewMatrix = view;
    _rhi->UpdateBuffer(_frameBuffer, &frameBufferData, sizeof(FrameBufferStructure));
    _rhi->SetBuffer(_frameBuffer, PipelineConstant::Get(EBufferSlot::FrameBuffer), EPipelineStage_VS | EPipelineStage_PS);

    // Update and upload light buffer
    LightsBufferStructure lightsData = {};
    for (const LightCommand& cmd : queue.GetLightCommands())
    {
        if (cmd.type == LightCommand::EType::Directional)
        {
            lightsData.directional.color = cmd.color;
            lightsData.directional.direction = cmd.forward;
        }
        if (cmd.type == LightCommand::EType::Ambient)
        {
            lightsData.ambient.color = cmd.color;
        }
    }
    _rhi->UpdateBuffer(_sceneLightBuffer, &lightsData, sizeof(LightsBufferStructure));
    _rhi->SetBuffer(_sceneLightBuffer, PipelineConstant::Get(EBufferSlot::LightBuffer), EPipelineStage_VS | EPipelineStage_PS);

    // Iterate all actual draw commands and draw them
    const Mesh* currentMesh = nullptr;

    for (const RenderCommand& cmd : queue.GetDrawCommands())
    {
        ObjectBufferStructure objectBufferData = {};
        objectBufferData.objectTransform = cmd.transform;
        _rhi->UpdateBuffer( _objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure) );
        _rhi->SetBuffer( _objectBuffer, PipelineConstant::Get(EBufferSlot::ObjectBuffer), EPipelineStage_VS | EPipelineStage_PS );

        _rhi->Draw(*cmd.pMesh, currentMesh != cmd.pMesh);
        currentMesh = cmd.pMesh;
    }

    _rhi->Present();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------