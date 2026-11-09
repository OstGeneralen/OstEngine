// Kasper "OstGeneralen" Esbjornsson - 2026
#include "PSOCache.h"

#include "RHI/RenderHardwareInterface.h"

#include <Memory/Memory.h>

using namespace ost;

// ------------------------------------------------------------

PSOCache::PSOCache(const RenderHardwareInterface& rhi)
    : _rhi{rhi}
    , _cache{}
{
    // Create shared vertex/input layouts
    _vertexLayouts.Insert(EVertexType::Position, {
                                                     {"POSITION", EDataSize::Float4}, // Pos
                                                 });

    _vertexLayouts.Insert(EVertexType::Blit, {
                                                 {"POSITION", EDataSize::Float4}, // Pos
                                                 {"TEXCOORD", EDataSize::Float2}, // UV
                                             });

    _vertexLayouts.Insert(EVertexType::Static, {
                                                   {"POSITION", EDataSize::Float4}, // Pos
                                                   {"NORMAL", EDataSize::Float3},   // Normal
                                                   {"TANGENT", EDataSize::Float3},  // Tangent
                                                   {"COLOR", EDataSize::Float4},    // Vertex Color
                                                   {"TEXCOORD", EDataSize::Float2}  // UV
                                               });

    // Create shared blend states
    _blendStates.Insert(EBlendState::Opaque, _rhi.CreateBlendState(EBlendState::Opaque));
    _blendStates.Insert(EBlendState::AlphaBlend, _rhi.CreateBlendState(EBlendState::AlphaBlend));
    _blendStates.Insert(EBlendState::Additive, _rhi.CreateBlendState(EBlendState::Additive));
}

PipelineStateObject& PSOCache::GetPSO(const GraphicsState& gfxState)
{
    if (PipelineStateObject* foundPSO = _cache.TryGetValue(gfxState))
    {
        return *foundPSO;
    }
    else
    {
        PipelineStateObjectDesc psoDesc = {};
        psoDesc.blendState = gfxState.blendState;
        psoDesc.topology = gfxState.primitiveTopology;
        psoDesc.inputLayout = _vertexLayouts[gfxState.vertexType];

        List<Uint8> vsBytecode(gfxState );
        MemCopy(vsBytecode.GetData(), gfxState.pVSBytecode, gfxState.vsBytecodeSize);
        _rhi.CreateShader(EPipelineStage::VS, vsBytecode, psoDesc.vertexShader);

        List<Uint8> psBytecode(gfxState.psBytecodeSize);
        MemCopy(psBytecode.GetData(), gfxState.pPSBytecode, gfxState.psBytecodeSize);
        _rhi.CreateShader(EPipelineStage::PS, vsBytecode, psoDesc.pixelShader);

        PipelineStateObject pso = {};
        _rhi.CreatePSO(psoDesc, pso);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------