// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Descriptors/TextureDesc.h"
#include "GraphicsEngine/Resources/Textures.h"

#include <Math/Color.h>

// ------------------------------------------------------------

namespace ost
{
    class IGfxTextureManager
    {
    public:
        virtual HTexture CreateFromDesc(const std::string& name, const TextureDesc& desc) = 0;
        virtual HTexture CreateCustom(const std::string& name, const Vector2u& dimensions, const List<RGBAColor32>& pixels) = 0;

        virtual const ITexture* Get(HTexture hnd) const = 0;

        virtual void Release(HTexture& hnd) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------