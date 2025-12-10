#pragma once
#include <OstEngine/Math/Vector2.h>
#include <SDL3/SDL_rect.h>

namespace ost
{
    template<typename T>
    struct SDLRectType
    {
        using Type = void;
    };

    template<>
    struct SDLRectType<Int32>;

    template<>
    struct SDLRectType<Float32>;

    template<>
    struct SDLRectType<Int32>
    {
        using Type = SDL_Rect;
    };
    template<>
    struct SDLRectType<Float32>
    {
        using Type = SDL_FRect;
    };


    template <typename T>
    struct TRect
    {
        TVector2<T> Point;
        TVector2<T> Dimensions;

        TRect() = default;
        TRect( const TVector2<T> aPoint, const TVector2<T>& aDimensions );
        TRect( const TRect& aOther ) = default;
        TRect& operator=( const TRect& aOther ) = default;

        SDLRectType<T>::Type ToSDLRect() const;
    };

    template <typename T>
    inline ost::TRect<T>::TRect( const TVector2<T> aPoint, const TVector2<T>& aDimensions )
        : Point{ aPoint }
        , Dimensions{ aDimensions }
    {
    }

    template <typename T>
    inline SDLRectType<T>::Type ost::TRect<T>::ToSDLRect() const
    {
        return { Point.X, Point.Y, Dimensions.X, Dimensions.Y };
    }

    using Recti = TRect<Int32>;
    using Rectf = TRect<Float32>;
} // namespace ost