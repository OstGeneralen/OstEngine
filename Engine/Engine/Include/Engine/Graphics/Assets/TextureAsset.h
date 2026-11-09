// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <utility>

#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class TextureAsset : public Asset
    {
    public:
        TextureAsset() = default;
        TextureAsset(HTexture texHnd)
            : _textureHandle{texHnd}
        {
        }
        TextureAsset(const TextureAsset&) = delete;
        TextureAsset(TextureAsset&& tex) noexcept = default;

        TextureAsset& operator=(const TextureAsset&) = delete;
        TextureAsset& operator=(TextureAsset&&) noexcept = default;

        HTexture GetTextureHandle() const
        {
            return _textureHandle;
        }

        TypeID AssetTypeID() const override
        {
            return TypeID::Get<TextureAsset>();
        }

    private:
        HTexture _textureHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------