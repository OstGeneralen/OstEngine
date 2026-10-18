// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderDefaultsLibrary.h"

#include "GraphicsEngine/Rendering/Vertex.h"
#include "Materials/MaterialCompiler.h"
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"
#include "Resources/GraphicsResourceManager.h"

using namespace ost;

// ------------------------------------------------------------

namespace defaults
{
    Mesh blitMesh;
    PipelineStateObject blitPSO;
} // namespace defaults

// ------------------------------------------------------------

void ost::RenderDefaultsLibrary::Initialize(const RenderHardwareInterface& rhi)
{
    // Create the blit mesh
    defaults::blitMesh.indexOffset = 0;
    defaults::blitMesh.indexCount = 6;
    defaults::blitMesh.vertexOffset = 0;
    defaults::blitMesh.vertexCount = 4;

    FullscreenVertex tl = {{-1, 1, 1, 1}, {0, 0}};
    FullscreenVertex tr = {{1, 1, 1, 1}, {1, 0}};
    FullscreenVertex br = {{1, -1, 1, 1}, {1, 1}};
    FullscreenVertex bl = {{-1, -1, 1, 1}, {0, 1}};

    FullscreenVertex vertices[4] = {tl, tr, bl, br};
    Uint32 indices[6] = {0, 1, 2, 2, 1, 3};
    rhi.CreateVertexBuffer(sizeof(FullscreenVertex), 4, vertices, defaults::blitMesh.vertexBuffer);
    rhi.CreateIndexBuffer(6, indices, defaults::blitMesh.indexBuffer);

    // Create the blit material (noop just copy colour!)
    MaterialDesc matDesc = {};
    matDesc.domain = EMaterialDomain::Blit;
    matDesc.materialShaderPath = "Engine/Shader/Material/MaterialShader_FullscreenBlit.hlsl";
    matDesc.blending = EBlendState::Opaque;

    MaterialCompiler matCompiler(matDesc);
    matCompiler.Compile();
    rhi.CreatePSO( matCompiler.GetCompiledPSODescForward(), defaults::blitPSO );
}

const Mesh& ost::RenderDefaultsLibrary::GetBlitMesh()
{
    return defaults::blitMesh;
}

const PipelineStateObject& ost::RenderDefaultsLibrary::GetBlitPSO()
{
    return defaults::blitPSO;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------