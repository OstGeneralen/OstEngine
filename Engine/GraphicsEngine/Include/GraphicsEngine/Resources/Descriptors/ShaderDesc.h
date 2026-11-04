// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct ShaderDesc
    {
        static ShaderDesc FromSourceCodePath( EPipelineStage stage, const std::string& path, const std::string& entry );

        EPipelineStage pipelineStage; // Bind point for the shader
        bool precompiled = false;     // True = code is Bytecode, False = code is Source Code
        List<Uint8> code;             // See "precompiled"

        // Data in this struct is only used when precompiled == false
        struct CompileInfo
        {
            std::string name;        // Name used when outputting i.e compiler errors
            std::string includeRoot; // Root directory path for includes for this shader
            std::string entryPoint;  // Entry point name of the shader program
        } compileInfo;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------