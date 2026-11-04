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
    {
        const std::string fn = std::vformat("{}_vs", std::make_format_args(n));
        _vertexShader.SetDebugName(fn);
    }
    {
        const std::string fn = std::vformat("{}_ps", std::make_format_args(n));
        _pixelShader.SetDebugName(fn);
    }
    if (_vertexLayout)
    {
        const std::string fn = std::vformat("{}_layout", std::make_format_args(n));
        _vertexLayout->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(fn.length()), fn.data());
    }
}

// ------------------------------------------------------------

const IShader* ost::PipelineStateObject::GetShader(EPipelineStage stage) const
{
    switch (stage)
    {
    case EPipelineStage::VS:
        return &_vertexShader;
    case EPipelineStage::PS:
        return &_pixelShader;
    }

    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------