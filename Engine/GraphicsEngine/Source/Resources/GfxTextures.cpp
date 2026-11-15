// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GfxTextures.h"

#include "RHI/RHIInternal.h"

using namespace ost;

DEFINE_GFX_RESOURCE_DEFAULTS(GfxTexture);

// ------------------------------------------------------------

GfxTexture::GfxTexture(ComPtr<RHITexture2D>&& t2d, ComPtr<RHIShaderResource>&& srv, ComPtr<RHIRenderTarget>&& rtv, ComPtr<RHIDepthStencil>&& dsv,
                       const Vector2u& dimensions)
    : _dimensions{dimensions}
    , _texture{std::move(t2d)}
    , _srv{std::move(srv)}
    , _rtv{std::move(rtv)}
    , _dsv{std::move(dsv)}
{
}

// ------------------------------------------------------------

const RHITexture2D* ost::GfxTexture::GetRHIPtrTexture2D() const
{
    return _texture.Get();
}

const RHIShaderResource* ost::GfxTexture::GetRHIPtrSrv() const
{
    return _srv.Get();
}

const RHIRenderTarget* ost::GfxTexture::GetRHIPtrRtv() const
{
    return _rtv.Get();
}

const RHIDepthStencil* ost::GfxTexture::GetRHIPtrDsv() const
{
    return _dsv.Get();
}

// ------------------------------------------------------------

const void* ost::GfxTexture::GetNativePtrSrv() const
{
    return GetRHIPtrSrv();
}

const void* ost::GfxTexture::GetNativePtrRtv() const
{
    return GetRHIPtrRtv();
}

const void* ost::GfxTexture::GetNativePtrDsv() const
{
    return GetRHIPtrDsv();
}

bool ost::GfxTexture::IsShaderResource() const
{
    return _srv;
}

bool ost::GfxTexture::IsRenderTarget() const
{
    return _rtv;
}

bool ost::GfxTexture::IsDepthStencilTarget() const
{
    return _dsv;
}

const Vector2u& ost::GfxTexture::GetDimensions() const
{
    return _dimensions;
}

// ------------------------------------------------------------

const void* ost::GfxTexture::GetNativeResourcePtr() const
{
    return _texture.Get();
}

void ost::GfxTexture::SetDebugName(const std::string& name) const
{
    if (_texture)
    {
        const std::string n = name + "_t2d";
        _texture->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(n.length()), n.data());
    }
    if (_srv)
    {
        const std::string n = name + "_srv";
        _srv->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(n.length()), n.data());
    }
    if (_dsv)
    {
        const std::string n = name + "_dsv";
        _dsv->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(n.length()), n.data());
    }
    if (_rtv)
    {
        const std::string n = name + "_rtv";
        _rtv->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(n.length()), n.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------