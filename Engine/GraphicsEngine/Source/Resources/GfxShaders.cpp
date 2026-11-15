// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GfxShaders.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------
// Vertex Shader
// ------------------------------------------------------------

DEFINE_GFX_RESOURCE_DEFAULTS(GfxVertexShader);

// ------------------------------------------------------------

GfxVertexShader::GfxVertexShader(ComPtr<RHIVertexShader>&& vs, EVertexType vertType)
    : _shader{std::move(vs)}
    , _vertexType{vertType}
{
}

const RHIVertexShader* GfxVertexShader::GetRHIPtr() const
{
    return _shader.Get();
}

EVertexType GfxVertexShader::GetVertexType() const
{
    return _vertexType;
}

const void* GfxVertexShader::GetNativeResourcePtr() const
{
    return GetRHIPtr();
}

void GfxVertexShader::SetDebugName(const std::string& name) const
{
    if (_shader)
    {
        _shader->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.length()), name.data());
    }
}

// ------------------------------------------------------------
// Pixel Shader
// ------------------------------------------------------------

ost::GfxPixelShader::GfxPixelShader(ComPtr<RHIPixelShader>&& ps, SizeType targetCount)
    : _shader{std::move(ps)}
    , _blendMode{blendMode}
    , _targetCount{targetCount}
{
}

const RHIPixelShader* ost::GfxPixelShader::GetRHIPtr() const
{
    return _shader.Get();
}

SizeType ost::GfxPixelShader::GetTargetCount() const
{
    return _targetCount;
}

const void* ost::GfxPixelShader::GetNativeResourcePtr() const
{
    return GetRHIPtr();
}

void ost::GfxPixelShader::SetDebugName(const std::string& name) const
{
    if (_shader)
    {
        _shader->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.length()), name.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------