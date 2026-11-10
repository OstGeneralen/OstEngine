// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Graphics/Material/MaterialClass.h"

#include <filesystem>

#include <GraphicsEngine/Resources/ShaderCompiler.h>
#include <Container/List.h>
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class MaterialCompiler
    {
    public:
        MaterialCompiler& SetDomain(EMaterialDomain domain);
        MaterialCompiler& SetLitMode(EMaterialLitMode mode);
        MaterialCompiler& SetMaterialHLSL(const std::filesystem::path& hlslPath);

        List<Uint8> CompileVertexShader() const;
        List<Uint8> CompilePixelShader() const;

    private:
        std::filesystem::path _vsPath;
        std::filesystem::path _psPath;
        std::filesystem::path _materialCodePath;
        List<std::string> _compileDefinitions;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------