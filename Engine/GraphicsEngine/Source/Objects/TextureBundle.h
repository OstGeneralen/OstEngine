// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct Texture;

    struct TextureBundle
    {
        TextureBundle();
        TextureBundle(const TextureBundle&);
        TextureBundle(TextureBundle&&) noexcept;
        TextureBundle(const List<const Texture*>& pTextures);
        ~TextureBundle();

        TextureBundle& operator=(const TextureBundle&);
        TextureBundle& operator=(TextureBundle&&) noexcept;

        List<const RHIShaderResource*> GetSRVList() const;

    private:
        List<ComPtr<RHIShaderResource>> _srvs;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------