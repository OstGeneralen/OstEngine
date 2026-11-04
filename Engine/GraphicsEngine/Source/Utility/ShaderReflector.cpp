// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Utility/ShaderReflector.h"

#include "Objects/Shader.h"
#include "RHI/RHIInternal.h"

#include <d3dcompiler.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

ost::ShaderReflector::ShaderReflector(const IShader& target)
{
    const auto& bytecode = target.GetBytecode();
    D3DReflect(bytecode.GetData(), bytecode.GetSize(), IID_ID3D11ShaderReflection, &_reflection);
}

ost::ShaderReflector::~ShaderReflector() = default;

// ------------------------------------------------------------



// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------