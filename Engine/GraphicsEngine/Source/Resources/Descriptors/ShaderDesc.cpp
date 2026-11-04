// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"

#include <filesystem>

#include <Utility/File.h>

using namespace ost;

namespace fs = std::filesystem;

// ------------------------------------------------------------

ShaderDesc ost::ShaderDesc::FromSourceCodePath(EPipelineStage stage, const std::string& path, const std::string& entry)
{
    fs::path loadPath = fs::weakly_canonical(path);

    ShaderDesc finalDesc = {};
    finalDesc.code = FileUtility::ReadFileToByteList(loadPath.string());
    finalDesc.pipelineStage = stage;
    finalDesc.precompiled = false;
    finalDesc.compileInfo.entryPoint = entry;
    finalDesc.compileInfo.name = std::format("{}#{}", loadPath.stem().string(), entry);
    finalDesc.compileInfo.includeRoot = loadPath.parent_path().string();

    return finalDesc;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------