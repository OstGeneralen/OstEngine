// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EDataFormat
    {
        // 4 channels
        RGBA_Float32,
        RGBA_Uint8,
        RGBA_Unorm8,

        // 3 channels
        RGB_Float32,

        // 2 channesl
        RG_Float32,
        RG_Uint8,
        RG_Unorm8,
        RG_Unorm16,

        // 1 channel
        R_Float32,
        R_Uint8,
        R_Unorm8,

        // Specific custom formats
        DDS_BC7,
        DDS_BC7_SRGB,

        DepthStencil,
    };

    // ------------------------------------------------------------

    enum class EDataSize
    {
        Float4,
        Float3,
        Float2,
        Float,

        Uint4,
        Uint3,
        Uint2,
        Uint,

        Byte4,
        Byte2,
        Byte,

        Unorm4,
        Unorm2,
        Unorm,
    };

    inline constexpr SizeType DataSizeByteCount(EDataSize s)
    {
        switch (s)
        {
        case EDataSize::Float4:
        case EDataSize::Uint4:
            return 16;

        case EDataSize::Float3:
        case EDataSize::Uint3:
            return 12;

        case EDataSize::Float2:
        case EDataSize::Uint2:
            return 8;

        case EDataSize::Float:
        case EDataSize::Uint:
        case EDataSize::Byte4:
        case EDataSize::Unorm4:
            return 4;

        case EDataSize::Byte2:
        case EDataSize::Unorm2:
            return 2;

        case EDataSize::Byte:
        case EDataSize::Unorm:
            return 1;
        }
        return 0;
    }

    // ------------------------------------------------------------

    enum class ETextureFormat
    {
        Unknown,
        RGBAUnorm,    // 4x 8-bit components (R8G8B8A8 unorm)
        NormalMap,    // 2x 16-bit components (R16G16 unorm)
        DDS_BC7,      // BC7 compressed dds
        DDS_BC7_SRGB, // BC7 compressed dds in SRGB
    };

    // ------------------------------------------------------------

    enum class EPrimitiveTopology
    {
        None = 0,
        PointList,
        LineList,
        TriangleList,
    };

    // ------------------------------------------------------------

    enum class EBlendMode : Uint32
    {
        Opaque = 0,
        AlphaBlend,
        Additive,
        COUNT,
        Unknown,
    };

    // ------------------------------------------------------------

    enum class EDepthMode : Uint32
    {
        Disabled,
        Less,
        LessEqual,
        Equal,
        COUNT,
        Unknown,
    };

    // ------------------------------------------------------------

    enum class EPipelineStage : Uint8
    {
        None = 0,
        VS = 1 << 0,
        PS = 1 << 2,
        All = VS | PS,
    };

    // ------------------------------------------------------------

    enum class ERenderPath
    {
        Forward,
        Deferred,
    };

} // namespace ost

// ------------------------------------------------------------

static inline ost::EPipelineStage operator|(ost::EPipelineStage a, ost::EPipelineStage b)
{
    return static_cast<ost::EPipelineStage>(static_cast<Uint8>(a) | static_cast<Uint8>(b));
}

static inline bool operator&(ost::EPipelineStage a, ost::EPipelineStage b)
{
    return (static_cast<Uint8>(a) & static_cast<Uint8>(b));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------