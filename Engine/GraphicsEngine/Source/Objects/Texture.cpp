// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Texture.h"

#include "RHI/RHIInternal.h"

#include <format>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

Texture::Texture() = default;
Texture::Texture(const Texture&) = default;
Texture::~Texture() = default;

void ost::Texture::SetDebugName(const std::string& name) const
{
    if (_dsv)
    {
        _dsv->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
    }
    if (_rtv)
    {
        _rtv->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
    }
    if (_srv)
    {
        _srv->SetPrivateData(WKPDID_D3DDebugObjectName, name.length(), name.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------