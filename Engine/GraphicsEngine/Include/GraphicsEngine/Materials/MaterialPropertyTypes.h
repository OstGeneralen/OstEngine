// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Color.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EMaterialPropertyType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Uint,
        Uint2,
        Uint3,
        Uint4,
        Color,
    };

    namespace MaterialPropertyType
    {
        constexpr inline SizeType GetByteSize(EMaterialPropertyType matPropType)
        {
            switch (matPropType)
            {
                // clang-format off
            case EMaterialPropertyType::Float:  return sizeof(Float32) * 1;
            case EMaterialPropertyType::Float2: return sizeof(Float32) * 2;
            case EMaterialPropertyType::Float3: return sizeof(Float32) * 3;
            case EMaterialPropertyType::Float4: return sizeof(Float32) * 4;
            case EMaterialPropertyType::Uint:   return sizeof(Uint32) * 1;
            case EMaterialPropertyType::Uint2:  return sizeof(Uint32) * 2;
            case EMaterialPropertyType::Uint3:  return sizeof(Uint32) * 3;
            case EMaterialPropertyType::Uint4:  return sizeof(Uint32) * 4;
            case EMaterialPropertyType::Color: return sizeof(Float32) * 4;
                // clang-format on
            }
            return 0;
        }

        template <typename T>
        constexpr inline bool TypeMatch(EMaterialPropertyType matPropType)
        {
            return false;
        }

        template <>
        constexpr inline bool TypeMatch<Float32>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Float;
        }

        template <>
        constexpr inline bool TypeMatch<Vector2f>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Float2;
        }

        template <>
        constexpr inline bool TypeMatch<Vector3f>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Float3;
        }

        template <>
        constexpr inline bool TypeMatch<Vector4f>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Float4;
        }

        template <>
        constexpr inline bool TypeMatch<Uint32>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Uint;
        }

        template <>
        constexpr inline bool TypeMatch<Vector2u>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Uint2;
        }

        template <>
        constexpr inline bool TypeMatch<Vector3u>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Uint3;
        }

        template <>
        constexpr inline bool TypeMatch<Vector3u>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Uint4;
        }

        template <>
        constexpr inline bool TypeMatch<Color>(EMaterialPropertyType matPropType)
        {
            return matPropType == EMaterialPropertyType::Color;
        }



    }; // namespace MaterialPropertyType

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------