// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Shader.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

Shader::Shader() = default;
Shader::Shader(const Shader&) = default;
Shader::Shader(Shader&&) noexcept = default;
Shader::~Shader() = default;

Shader& Shader::operator=(const Shader&) = default;
Shader& Shader::operator=(Shader&&) noexcept = default;

// ------------------------------------------------------------

void ost::Shader::SetDebugName(const std::string& name) const
{
    if (_vs)
    {
        _vs->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
    }
    if (_ps)
    {
        _ps->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
    }
}

// ------------------------------------------------------------

ost::Shader::operator bool() const
{
    switch (_stage)
    {
    case EPipelineStage::VS:
        return _vs;
    case EPipelineStage::PS:
        return _ps;
    }
    return false;
}

// ------------------------------------------------------------

const BufferView& ost::Shader::GetBytecode() const
{
    return _bytecode;
}

EPipelineStage ost::Shader::GetPipelineStage() const
{
    return _stage;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------