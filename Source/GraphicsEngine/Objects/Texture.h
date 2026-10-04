// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/RHI/RHIMinimal.h"

#include <OstTypes.h>

#include <Container/List.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct ResourceTextureDesc
    {
        Uint32 mipCount = 1;
        EDataFormat format = EDataFormat::RGBA_Unorm8;

        struct ImageData
        {
            Uint32 pitch;
            Uint32 slice;
            SizeType numBytes;
            void* pData;
        };

        List<ImageData> images;
        Vector2u dimensions;
    };

    struct Texture
    {
        friend class RenderHardwareInterface;

        Texture();
        Texture(const Texture&);
        ~Texture();

    private:
        ComPtr<RHIRenderTarget> _rtv;
        ComPtr<RHIShaderResource> _srv;
        ComPtr<RHIDepthStencil> _dsv;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------