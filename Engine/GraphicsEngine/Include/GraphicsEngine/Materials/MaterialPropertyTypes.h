// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/MaterialConstants.h"

#include <Math/Color.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EMaterialPropertyType
    {
        Unknown,
        Float,
        Float2,
        Float3,
        Float4,
        Uint,
        Uint2,
        Uint3,
        Uint4,
    };

    namespace MaterialPropertyType
    {

        constexpr inline SizeType GetByteSize(EMaterialPropertyType t)
        {
            switch (t)
            {
            case EMaterialPropertyType::Float:
            case EMaterialPropertyType::Uint:
                return 4;
            case EMaterialPropertyType::Float2:
            case EMaterialPropertyType::Uint2:
                return 8;
            case EMaterialPropertyType::Float3:
            case EMaterialPropertyType::Uint3:
                return 12;
            case EMaterialPropertyType::Float4:
            case EMaterialPropertyType::Uint4:
                return 16;
            }
            return 0;
        }

        template <typename CheckType>
        constexpr inline bool MatchType(EMaterialPropertyType t)
        {
            return false;
        }

#define MAKE_PROPERTY_TYPE(propType, type)                                                                                                                               \
    template <>                                                                                                                                                          \
    constexpr inline bool MatchType<type>(EMaterialPropertyType propertyType)                                                                                            \
    {                                                                                                                                                                    \
        return propertyType == propType;                                                                                                                                 \
    }

        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Float, Float32);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Float2, Vector2f);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Float3, Vector3f);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Float4, Vector4f);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Uint, Uint32);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Uint2, Vector2u);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Uint3, Vector3u);
        MAKE_PROPERTY_TYPE(EMaterialPropertyType::Uint4, Vector4u);
    } // namespace MaterialPropertyType

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------