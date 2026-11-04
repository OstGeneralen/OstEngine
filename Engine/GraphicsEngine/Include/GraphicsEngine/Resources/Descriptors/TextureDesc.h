// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <Container/List.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    struct TextureImageDesc
    {
        SizeType rowPitch;
        SizeType slicePitch;
        List<Uint8> data;
    };

    struct TextureDesc
    {
        Uint32 mipCount = 1;
        ETextureFormat format = ETextureFormat::Unknown;
        Uint32 dimensionCount = 2;
        Vector3u dimensions;
        List<TextureImageDesc> images;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------