// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ShaderFactory.h"

#include "Engine/Graphics/Assets/ShaderAsset.h"

#include <filesystem>
#include <fstream>

#include <Container/List.h>
#include <GraphicsEngine/Resources/ShaderCompiler.h>
#include <Utility/File.h>
#include <nlohmann/json.hpp>

using namespace ost;

namespace fs = std::filesystem;
namespace nm = nlohmann;

// ------------------------------------------------------------

TypeID ost::ShaderFactory::AssetTypeID() const
{
    return TypeID::Get<ShaderAsset>();
}

// ------------------------------------------------------------

Asset* ost::ShaderFactory::ConstructDefault() const
{
    return new ShaderAsset();
}

// ------------------------------------------------------------

void ost::ShaderFactory::Load(const std::filesystem::path& path, Asset* pInto) const
{
    // 1. Read the json file containing the shader info
    nm::json shaderJson;
    {
        std::ifstream rdStream(path);
        rdStream >> shaderJson;
    }

    const std::string shaderJsonPath = shaderJson["path"].get<std::string>();
    const std::string shaderJsonEntry = shaderJson["entry"].get<std::string>();
    const std::string shaderJsonType = shaderJson["type"].get<std::string>();

    // 2. Convert the json properties to usable properties
    const fs::path shaderPath = fs::weakly_canonical(shaderJson["path"].get<std::string>());
    const std::string shaderName = shaderPath.stem().string();
    EPipelineStage stage = EPipelineStage::None;
    if (shaderJsonType[0] == 'P')
    {
        stage = EPipelineStage::PS;
    }
    else if (shaderJsonType[0] == 'V')
    {
        stage = EPipelineStage::VS;
    }

    // 4. Populate the ShaderSource structure
    ShaderSource src;
    src.includeRoot = shaderPath.parent_path();
    src.shaderName = shaderPath.stem().string();
    src.shaderEntryPoint = shaderJsonEntry;
    src.pipelineStage = stage;
    src.sourceCode = FileUtility::ReadFileToByteList(shaderPath.string());

    // 5. Compile the Shader Code and construct the shader asset
    static_cast<ShaderAsset&>(*pInto) = std::move(ShaderAsset(src.pipelineStage, ShaderCompiler::Compile(src)));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------