// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"
#include "Math/Vector2.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    enum class ETextureFormat
    {
        Unknown,
        DDS_BC7,
        DDS_BC7_SRGB,
    };

    struct TextureCPUData
    {
        SizeType mipCount = 1;
        ETextureFormat format = ETextureFormat::Unknown;

        struct ImageData
        {
            SizeType rowPitch;
            SizeType slicePitch;
            List<Uint8> data;
        };

        Vector2u dimensions;
        List<ImageData> images;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------