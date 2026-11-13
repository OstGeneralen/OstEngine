// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Interfaces/IShader.h"

#include <wrl.h>

// ------------------------------------------------------------

struct ID3D11ShaderReflection;

// ------------------------------------------------------------

namespace ost
{

    class ShaderReflector
    {
    public:
        ShaderReflector(const IShader& target);
        ~ShaderReflector();

    private:
        Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflection;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------