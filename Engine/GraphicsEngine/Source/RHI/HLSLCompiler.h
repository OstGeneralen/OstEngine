// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class HLSLCompiler
    {
    public:
        List<Uint8> CompileVertexShader(const std::string& shaderName, const List<Uint8>& code, const std::string& entry, const std::string& rootInclude)
        {
            return Compile(shaderName, EPipelineStage::VS, code, entry, rootInclude);
        }

        List<Uint8> CompilePixelShader(const std::string& shaderName, const List<Uint8>& code, const std::string& entry, const std::string& rootInclude)
        {
            return Compile(shaderName, EPipelineStage::PS, code, entry, rootInclude);
        }

        List<Uint8> Compile(const std::string& shaderName, EPipelineStage shaderStage, const List<Uint8>& code, const std::string& entry,
                            const std::string& rootInclude);

    private:
        std::string _entry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------