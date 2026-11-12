// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialManager.h"

#include "MaterialCompiler.h"

#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>
#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

HMaterialClass ost::MaterialManager::CreateClass(const MaterialDesc& desc)
{

    MaterialCompiler compiler;
    compiler.SetDomain(desc.domain).SetLitMode(desc.litMode).SetMaterialHLSL(desc.materialShaderPath);

    const auto psBytecode = compiler.CompilePixelShader();
    const auto vsBytecode = compiler.CompileVertexShader();

    ShaderDesc psDesc;
    psDesc.pipelineStage = EPipelineStage::PS;
    psDesc.bytecodeView = psBytecode;

    ShaderDesc vsDesc;
    vsDesc.pipelineStage = EPipelineStage::VS;
    vsDesc.bytecodeView = vsBytecode;

    // Build the actual material class
    MaterialClass materialClass;
    materialClass._blendMode = EBlendMode::Opaque;
    materialClass._domain = desc.domain;
    materialClass._litMode = desc.litMode;
    materialClass._renderTopology = EPrimitiveTopology::TriangleList;
    materialClass._pixelShaderHandle = _graphicsResources.CreateShader(psDesc);
    materialClass._vertexShaderHandle = _graphicsResources.CreateShader(vsDesc);

    return HMaterialClass{_classes.Add(std::move(materialClass))};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------