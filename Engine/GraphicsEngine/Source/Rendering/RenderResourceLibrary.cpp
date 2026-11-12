// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderResourceLibrary.h"

#include "GraphicsEngine/Resources/ShaderCompiler.h"
#include "RHI/RenderHardwareInterface.h"

#include <Memory/Memory.h>
#include <Utility/Assert.h>

// ------------------------------------------------------------

ost::RenderResourceLibrary* ost::RenderResourceLibrary::pInstance = nullptr;

using namespace ost;

// ------------------------------------------------------------

const RenderResourceLibrary& ost::RenderResourceLibrary::Get()
{
    return *pInstance;
}

// ------------------------------------------------------------

ost::RenderResourceLibrary::RenderResourceLibrary()
{
    OST_ASSERT(pInstance == nullptr, "Only one render resource library allowed");
    pInstance = this;
}

ost::RenderResourceLibrary::~RenderResourceLibrary()
{
    pInstance = nullptr;
}

// ------------------------------------------------------------

void ost::RenderResourceLibrary::InitializeResources(const RenderHardwareInterface& rhi)
{
    InitializeBlitResources(rhi);
    InitializeStateObjects(rhi);
}

// ------------------------------------------------------------

const RenderResourceMesh& ost::RenderResourceLibrary::GetBlitMesh() const
{
    return _blitMesh;
}

const Shader& ost::RenderResourceLibrary::GetBlitVertexShader() const
{
    return _blitVertexShader;
}

const Shader& ost::RenderResourceLibrary::GetBlitPixelShader() const
{
    return _blitPixelShader;
}

// ------------------------------------------------------------

const BlendState& ost::RenderResourceLibrary::GetBlendState(EBlendMode blendMode) const
{
    return _blendStates[static_cast<Uint32>(blendMode)];
}

const DepthStencilState& ost::RenderResourceLibrary::GetDepthStencilState(EDepthMode depthMode) const
{
    return _dsStates[static_cast<Uint32>(depthMode)];
}

// ------------------------------------------------------------

void ost::RenderResourceLibrary::InitializeStateObjects(const RenderHardwareInterface& rhi)
{
    rhi.CreateBlendState(EBlendMode::Opaque, _blendStates[static_cast<Uint32>(EBlendMode::Opaque)]);
    rhi.CreateBlendState(EBlendMode::AlphaBlend, _blendStates[static_cast<Uint32>(EBlendMode::AlphaBlend)]);
    rhi.CreateBlendState(EBlendMode::Additive, _blendStates[static_cast<Uint32>(EBlendMode::Additive)]);

    rhi.CreateDepthStencilState(EDepthMode::Disabled, _dsStates[static_cast<Uint32>(EDepthMode::Disabled)]);
    rhi.CreateDepthStencilState(EDepthMode::Less, _dsStates[static_cast<Uint32>(EDepthMode::Less)]);
    rhi.CreateDepthStencilState(EDepthMode::LessEqual, _dsStates[static_cast<Uint32>(EDepthMode::LessEqual)]);
    rhi.CreateDepthStencilState(EDepthMode::Equal, _dsStates[static_cast<Uint32>(EDepthMode::Equal)]);
}

void ost::RenderResourceLibrary::InitializeBlitResources(const RenderHardwareInterface& rhi)
{
    { // Blit Mesh
        // clang-format off
        BlitVertex blitVerts[4] = {
            {{-1, 1, 0, 1}, {-1, -1}},
            {{1, 1, 0, 1}, {1, -1}},
            {{1, -1, 0, 1}, {1, 1}},
            {{-1, -1, 0, 1}, {-1, 1}}
        };
        // clang-format on
        rhi.CreateVertexBuffer(sizeof(BlitVertex), 4, blitVerts, _blitMesh.vertexBuffer);

        Uint32 blitIndices[6] = {0, 1, 3, 1, 2, 3};
        rhi.CreateIndexBuffer(6, blitIndices, _blitMesh.indexBuffer);

        _blitMesh.vertexType = EVertexType::Blit;
        _blitMesh.indexCount = 6;
    }

    { // Blit Vertex Shader
        static std::string_view blitVSCode = "#include \"Shared/ShaderCommon.hlsli\""
                                             "#include \"Shared/LayoutsMaster.hlsli\""
                                             "#include \"Shared/Resources.hlsli\""
                                             "BlitPixel VSMain(BlitVertex vertex) {"
                                             "BlitPixel output;"
                                             "output.Position = vertex.Position;"
                                             "output.UV = vertex.UV;"
                                             "return output;"
                                             "};";

        ShaderSource blitVSSrc;
        blitVSSrc.sourceCode = List<Uint8>(blitVSCode.size());
        MemCopy(blitVSSrc.sourceCode.GetData(), blitVSCode.data(), blitVSSrc.sourceCode.GetSize());

        blitVSSrc.includeRoot = "Engine/Shader";
        blitVSSrc.shaderName = "BlitShaderVS";
        blitVSSrc.shaderEntryPoint = "VSMain";

        rhi.CreateShader(EPipelineStage::VS, ShaderCompiler::Compile(blitVSSrc), _blitVertexShader);
    }

    { // Blit Pixel Shader

        static std::string_view blitPSCode = "#include \"Shared/ShaderCommon.hlsli\""
                                             "#include \"Shared/LayoutsMaster.hlsli\""
                                             "#include \"Shared/Resources.hlsli\""
                                             "Texture2D tex_blitSource : register(t0);"
                                             "float4 PSMain(BlitFragment frag) : SV_Target {"
                                             "float3 outputColor = tex_blitSource.Sample(PointClamp, frag.UV).rgb;"
                                             "return float4(outputColor, 1);"
                                             "};";

        ShaderSource blitPSSrc;

        blitPSSrc.sourceCode = List<Uint8>(blitPSCode.size());
        MemCopy(blitPSSrc.sourceCode.GetData(), blitPSCode.data(), blitPSSrc.sourceCode.GetSize());

        blitPSSrc.includeRoot = "Engine/Shader";
        blitPSSrc.shaderName = "BlitShaderPS";
        blitPSSrc.shaderEntryPoint = "PSMain";

        rhi.CreateShader(EPipelineStage::PS, ShaderCompiler::Compile(blitPSSrc), _blitPixelShader);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------