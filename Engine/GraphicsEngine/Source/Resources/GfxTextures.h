// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Textures.h"
#include "RHI/RHIMinimal.h"
#include "Resources/GfxResourceHelper.h"

// ------------------------------------------------------------

namespace ost
{
    class GfxTexture : public ITexture
    {
    public:
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxTexture);

        GfxTexture(ComPtr<RHITexture2D>&& t2d, ComPtr<RHIShaderResource>&& srv, ComPtr<RHIRenderTarget>&& rtv, ComPtr<RHIDepthStencil>&& dsv, const Vector2u& dimensions);

        const RHITexture2D* GetRHIPtrTexture2D() const;
        const RHIShaderResource* GetRHIPtrSrv() const;
        const RHIRenderTarget* GetRHIPtrRtv() const;
        const RHIDepthStencil* GetRHIPtrDsv() const;

        // BEGIN ITexture
        const void* GetNativePtrSrv() const override;
        const void* GetNativePtrRtv() const override;
        const void* GetNativePtrDsv() const override;

        bool IsShaderResource() const override;
        bool IsRenderTarget() const override;
        bool IsDepthStencilTarget() const override;

        const Vector2u& GetDimensions() const override;
        // END ITexture

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource

    private:
        Vector2u _dimensions;
        ComPtr<RHITexture2D> _texture;
        ComPtr<RHIShaderResource> _srv;
        ComPtr<RHIRenderTarget> _rtv;
        ComPtr<RHIDepthStencil> _dsv;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------