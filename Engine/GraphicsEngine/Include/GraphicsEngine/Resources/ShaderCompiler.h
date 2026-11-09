// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>
#include <filesystem>
#include <string>

#include <Container/List.h>
#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    struct ShaderSource
    {
        List<Uint8> sourceCode;
        EPipelineStage pipelineStage;
        std::string shaderName;
        std::string shaderEntryPoint;
        std::filesystem::path includeRoot = std::filesystem::current_path();
        Map<std::string, std::filesystem::path> includeRemapping;
    };

    class ShaderCompiler
    {
    public:
        static List<Uint8> Compile(const ShaderSource& shaderSource);
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------