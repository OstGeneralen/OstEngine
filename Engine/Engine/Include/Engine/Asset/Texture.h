// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <utility>

#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class Texture : public Asset
    {
    public:
        Texture() = default;
        Texture(HTexture texHnd)
            : _textureHandle{texHnd}
        {
        }
        Texture(const Texture&) = delete;
        Texture(Texture&& tex) noexcept = default;

        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) noexcept = default;

        HTexture GetTextureHandle() const
        {
            return _textureHandle;
        }

        TypeID AssetTypeID() const override
        {
            return TypeID::Get<Texture>();
        }

    private:
        HTexture _textureHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------