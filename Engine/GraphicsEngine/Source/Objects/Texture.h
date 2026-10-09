// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

#include <OstTypes.h>

#include <Container/List.h>
#include <Math/Vector2.h>

#include <string>

// ------------------------------------------------------------

namespace ost
{
    struct Texture
    {
        friend class RenderHardwareInterface;

        Texture();
        Texture(const Texture&);
        ~Texture();

        void SetDebugName( const std::string& name ) const;

    private:
        ComPtr<RHIRenderTarget> _rtv;
        ComPtr<RHIShaderResource> _srv;
        ComPtr<RHIDepthStencil> _dsv;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------