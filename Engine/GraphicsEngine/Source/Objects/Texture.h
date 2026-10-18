// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ITexture.h"
#include "RHI/RHIMinimal.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct Texture : public ITexture
    {
        friend class RenderHardwareInterface;

        Texture();
        Texture(const Texture&);
        ~Texture();

        void SetDebugName(const std::string& name) const;

    private:
        ComPtr<RHIRenderTarget> _rtv;
        ComPtr<RHIShaderResource> _srv;
        ComPtr<RHIDepthStencil> _dsv;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------