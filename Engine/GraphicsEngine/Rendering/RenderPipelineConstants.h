// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------
// NOTE: Make sure these always match 1-1 with the relevant
// resource binding in EngineAssets/Shaders/ShaderSlots.hlsli
// ------------------------------------------------------------

namespace ost
{
    enum class ETextureSlot : Uint32
    {
        Material0,
        Material1,
        Material2,
        Material3,
        Material4,
        Material5,
        Material6,
        Material7,
        Albedo,
        Normal,
        ORM,
    };

    enum class ESamplerSlot : Uint32
    {
        PointWrap = 0,
        BilinearWrap = 1,
        TrilinearWrap = 2,
        PointClamp = 3,
        BilinearClamp = 4,
        TrilinearClamp = 5,
    };

    enum class EBufferSlot : Uint32
    {
        MaterialProperties = 0,

        FrameBuffer = 10,
        ObjectBuffer = 11,
        LightBuffer = 12,
        Animation = 13,
    };

    namespace PipelineConstant
    {
        inline static Uint32 Get(ETextureSlot s) noexcept
        {
            return static_cast<Uint32>(s);
        }

        inline static Uint32 Get(ESamplerSlot s) noexcept
        {
            return static_cast<Uint32>(s);
        }

        inline static Uint32 Get(EBufferSlot s) noexcept
        {
            return static_cast<Uint32>(s);
        }
    }; // namespace PipelineConstant

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------