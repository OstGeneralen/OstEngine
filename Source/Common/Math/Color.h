// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Math/Math.h>

// ------------------------------------------------------------

namespace ost
{
    struct RGBAColor32
    {
        union {
            Uint32 RGBA;
            struct
            {
                Uint8 R, G, B, A;
            };
            Uint8 arr[4];
        };

        RGBAColor32()
            : R{0}
            , G{0}
            , B{0}
            , A{255}
        {
        }

        constexpr RGBAColor32(Uint32 u32)
            : RGBA{u32}
        {
        }

        constexpr RGBAColor32(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
            : R{r}
            , G{g}
            , B{b}
            , A{a}
        {
        }

        constexpr RGBAColor32(const RGBAColor32& o)
            : RGBA{o.RGBA}
        {
        }
    };

    struct Color
    {
        union {
            Float32 FltArray[4];
            struct
            {
                Float32 R, G, B, A;
            };
        };

        Color()
            : R{0}
            , G{0}
            , B{0}
            , A{0}
        {
        }

        constexpr Color(Float32 r, Float32 g, Float32 b, Float32 a)
            : R{r}
            , G{g}
            , B{b}
            , A{a}
        {
        }

        constexpr Color(const RGBAColor32& u32)
            : R{static_cast<Float32>(u32.R) / 255.0f}
            , G{static_cast<Float32>(u32.G) / 255.0f}
            , B{static_cast<Float32>(u32.B) / 255.0f}
            , A{static_cast<Float32>(u32.A) / 255.0f}
        {
        }

        constexpr Color& operator=(const Color& rhs)
        {
            R = rhs.R;
            G = rhs.G;
            B = rhs.B;
            A = rhs.A;
            return *this;
        }

        constexpr Color& operator=(const RGBAColor32& rhs)
        {
            R = static_cast<Float32>(rhs.R) / 255.0f;
            G = static_cast<Float32>(rhs.G) / 255.0f;
            B = static_cast<Float32>(rhs.B) / 255.0f;
            A = static_cast<Float32>(rhs.A) / 255.0f;
            return *this;
        }

        constexpr inline operator RGBAColor32() const
        {
            return RGBAColor32{static_cast<Uint8>(math::Clamp<Float32>(R / 255.0f, 0, 255.0f)), static_cast<Uint8>(math::Clamp<Float32>(G / 255.0f, 0, 255.0f)),
                               static_cast<Uint8>(math::Clamp<Float32>(B / 255.0f, 0, 255.0f)), static_cast<Uint8>(math::Clamp<Float32>(A / 255.0f, 0, 255.0f))};
        }
    };

    namespace Colors
    {
        static constexpr Color Black{0, 0, 0, 1};
        static constexpr Color White{1, 1, 1, 1};
        static constexpr Color Red{1, 0, 0, 1};
        static constexpr Color Green{0, 1, 0, 1};
        static constexpr Color Blue{0, 0, 1, 1};
        static constexpr Color Yellow{1, 1, 0, 1};
        static constexpr Color Magenta{1, 0, 1, 1};
        static constexpr Color Cyan{0, 1, 1, 1};

        static constexpr RGBAColor32 Black32{0, 0, 0, 255};
        static constexpr RGBAColor32 White32{255, 255, 255, 255};
        static constexpr RGBAColor32 Red32{255, 0, 0, 255};
        static constexpr RGBAColor32 Green32{0, 255, 0, 255};
        static constexpr RGBAColor32 Blue32{0, 0, 255, 255};
        static constexpr RGBAColor32 Yellow32{255, 255, 0, 255};
        static constexpr RGBAColor32 Magenta32{255, 0, 255, 255};
        static constexpr RGBAColor32 Cyan32{0, 255, 255, 255};
    } // namespace Colors

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------