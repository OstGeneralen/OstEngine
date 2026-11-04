// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EShaderCodeFormat
    {
        Precompiled, // Compiled bytecode ready to use
        Source,      // Plain hlsl that needs compiling before use
    };

    struct ShaderCPUData
    {
        EPipelineStage pipelineStage; // Bind point for the shader
        EShaderCodeFormat format;     // Precompiled or Source code?
        std::string includeRoot;      // Only used if format is source
        std::string entryPoint;       // Only used if format is source
        List<Uint8> code;             // Format is source: Source Code, Format is precompiled: Bytecode
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------