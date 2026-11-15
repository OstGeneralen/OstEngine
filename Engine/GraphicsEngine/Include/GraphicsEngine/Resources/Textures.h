// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/IGraphicsResource.h"

#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HTexture);

    // ------------------------------------------------------------

    struct ITexture : public IGraphicsResource
    {
        virtual const void* GetNativePtrSrv() const = 0;
        virtual const void* GetNativePtrRtv() const = 0;
        virtual const void* GetNativePtrDsv() const = 0;

        virtual bool IsShaderResource() const = 0;
        virtual bool IsRenderTarget() const = 0;
        virtual bool IsDepthStencilTarget() const = 0;

        virtual const Vector2u& GetDimensions() const = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------