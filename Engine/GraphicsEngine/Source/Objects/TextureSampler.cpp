// Kasper "OstGeneralen" Esbjornsson - 2026
#include "TextureSampler.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

TextureSampler::TextureSampler() = default;
TextureSampler::TextureSampler(const TextureSampler&) = default;
TextureSampler::~TextureSampler() = default;

// ------------------------------------------------------------

void ost::TextureSampler::SetDebugName(const std::string& name)
{
    _samplerState->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------