// Kasper "OstGeneralen" Esbjornsson - 2026
#include "PipelineStateObject.h"

#include "RHI/RHIInternal.h"

#include <format>

using namespace ost;

// ------------------------------------------------------------

PipelineStateObject::PipelineStateObject() = default;
PipelineStateObject::PipelineStateObject(const PipelineStateObject&) = default;
PipelineStateObject::~PipelineStateObject() = default;

void ost::PipelineStateObject::SetDebugName(const std::string& n) const
{
    if (_vertexShader)
    {
        const std::string fn = std::vformat("{}_vs", std::make_format_args(n));
        _vertexShader->SetPrivateData(WKPDID_D3DDebugObjectName, fn.length(), fn.data());
    }
    if (_pixelShader)
    {
        const std::string fn = std::vformat("{}_ps", std::make_format_args(n));
        _pixelShader->SetPrivateData(WKPDID_D3DDebugObjectName, fn.length(), fn.data());
    }
    if (_vertexLayout)
    {
        const std::string fn = std::vformat("{}_layout", std::make_format_args(n));
        _vertexLayout->SetPrivateData(WKPDID_D3DDebugObjectName, fn.length(), fn.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------