// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialCompiler.h"

#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

MaterialCompiler& MaterialCompiler::SetDomain(EMaterialDomain domain)
{
    _compileDefinitions.Clear();
    _compileDefinitions.Add("SHADER_VARIANT_MATERIAL");

    _vsPath = std::filesystem::weakly_canonical("Engine/Shader/VSMaster.hlsl");

    switch (domain)
    {
    case EMaterialDomain::SurfaceOpaque:
        _compileDefinitions.Add("SHADER_VARIANT_SURFACE_STATIC");
        _psPath = std::filesystem::weakly_canonical("Engine/Shader/Material/SurfaceOpaque.hlsl");
        break;
    case EMaterialDomain::PostProcess:
        _compileDefinitions.Add("SHADER_VARIANT_BLIT");
        _psPath = std::filesystem::weakly_canonical("Engine/Shader/Material/PostProcess.hlsl");
        break;
    }

    return *this;
}

MaterialCompiler& ost::MaterialCompiler::SetLitMode(EMaterialLitMode mode)
{
    // Not yet supported
    return *this;
}

MaterialCompiler& ost::MaterialCompiler::SetMaterialHLSL(const std::filesystem::path& hlslPath)
{
    _materialCodePath = std::filesystem::weakly_canonical(hlslPath);
    return *this;
}

// ------------------------------------------------------------

List<Uint8> ost::MaterialCompiler::CompileVertexShader() const
{
    ShaderSource source;
    source.definitions = _compileDefinitions;
    source.includeRoot = _vsPath.parent_path();
    source.pipelineStage = EPipelineStage::VS;
    source.shaderEntryPoint = "VSMain";
    source.shaderName = _materialCodePath.stem().string() + "_VS";
    source.sourceCode = FileUtility::ReadFileToByteList(_vsPath.string());

    return ShaderCompiler::Compile(source);
}

List<Uint8> ost::MaterialCompiler::CompilePixelShader() const
{
    ShaderSource source;
    source.definitions = _compileDefinitions;
    source.includeRemapping.Insert("MATERIAL", _materialCodePath);
    source.includeRoot = _psPath.parent_path();
    source.pipelineStage = EPipelineStage::PS;
    source.shaderEntryPoint = "PSMain";
    source.shaderName = _materialCodePath.stem().string() + "_PS";
    source.sourceCode = FileUtility::ReadFileToByteList(_psPath.string());

    return ShaderCompiler::Compile(source);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------