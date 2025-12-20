#pragma once
#include "OstEngine/Common/Math/DxMath.h"
#include "OstEngine/Common/Utility/NumericUtils.h"
#include "OstEngine/Types.h"

#include <cmath>

namespace ost
{
    // ------------------------------------------------------------
    // Declaration
    // ------------------------------------------------------------
    template <typename T>
    class TVector2
    {
    public:
        using DxVecUtil = DxVecTypeUtility<T, 2>;

        // clang-format off
        union
        {
            DxVecUtil::DxVecType Vec;
            struct { T X, Y; };
        };
        // clang-format on

        TVector2();
        TVector2( const T aX, const T aY );

        TVector2( const TVector2& ) = default;
        TVector2( TVector2&& ) noexcept = default;

        TVector2& operator=( const TVector2& ) = default;
        TVector2& operator=( TVector2&& ) noexcept = default;

        template <typename TargetType>
        TVector2<TargetType> ToType() const;

        T Dot( const TVector2& aOther ) const;

        T MagnitudeSqr() const;
        T Magnitude() const;

        TVector2 GetNormalized() const;
        TVector2& Normalize();

        TVector2<T>& operator+=( const TVector2& aOther );
        TVector2<T>& operator-=( const TVector2& aOther );
        TVector2<T>& operator*=( const T aScalar );
        TVector2<T>& operator/=( const T aScalar );

        TVector2<T> operator+( const TVector2& aOther ) const;
        TVector2<T> operator-( const TVector2& aOther ) const;
        TVector2<T> operator*( const T aOther ) const;
        TVector2<T> operator/( const T aOther ) const;

        bool operator==( const TVector2& aOther ) const;
    };

    // ------------------------------------------------------------
    // Typed Vector3s
    // ------------------------------------------------------------
    using Vector2f = TVector2<Float32>;
    using Vector2i = TVector2<Int32>;
    using Vector2u = TVector2<Uint32>;
    // ------------------------------------------------------------

    // ------------------------------------------------------------
    // Begin Definition
    // ------------------------------------------------------------
    template <typename T>
    inline ost::TVector2<T>::TVector2()
        : X{ static_cast<T>( 0 ) }
        , Y{ static_cast<T>( 0 ) }
    {
    }

    template <typename T>
    inline ost::TVector2<T>::TVector2( const T aX, const T aY )
        : X{ aX }
        , Y{ aY }
    {
    }

    template <typename T>
    template <typename TargetType>
    inline TVector2<TargetType> ost::TVector2<T>::ToType() const
    {
        return TVector2<TargetType>( static_cast<TargetType>( X ), static_cast<TargetType>( Y ) );
    }

    template <typename T>
    inline T ost::TVector2<T>::Dot( const TVector2& aOther ) const
    {
        T result;
        DxVecUtil::StoreSingle( result,
                                DirectX::XMVector2Dot( DxVecUtil::ToXMVec( Vec ), DxVecUtil::ToXMVec( aOther.Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector2<T>::MagnitudeSqr() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector2LengthSq( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector2<T>::Magnitude() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector2Length( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector2<T> ost::TVector2<T>::GetNormalized() const
    {
        TVector2 result;
        DxVecUtil::Store( result.Vec, DirectX::XMVector2Normalize( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::Normalize()
    {
        DxVecUtil::Store( Vec, DirectX::XMVector2Normalize( DxVecUtil::ToXMVec( Vec ) ) );
        return *this;
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::operator+=( const TVector2& aOther )
    {
        X += aOther.X;
        Y += aOther.Y;
        return *this;
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::operator-=( const TVector2& aOther )
    {
        X -= aOther.X;
        Y -= aOther.Y;
        return *this;
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::operator*=( const T aScalar )
    {
        X *= aScalar;
        Y *= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::operator/=( const T aScalar )
    {
        X /= aScalar;
        Y /= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator+( const TVector2<T>& aSecond ) const
    {
        return TVector2<T>( X + aSecond.X, Y + aSecond.Y );
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator-( const TVector2<T>& aSecond ) const
    {
        return TVector2<T>( X - aSecond.X, Y - aSecond.Y );
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator*( const T aScalar ) const
    {
        return TVector2<T>( X * aScalar, Y * aScalar );
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator/( const T aScalar ) const
    {
        return TVector2<T>( X / aScalar, Y / aScalar );
    }

    template <typename T>
    inline bool TVector2<T>::operator==( const TVector2<T>& aSecond ) const
    {
        return ( X == aSecond.X ) && ( Y == aSecond.Y );
    }

    template <>
    inline bool TVector2<Float32>::operator==( const TVector2<Float32>& aSecond ) const
    {
        return util::numeric::NearlyEqual( X, aSecond.X ) && util::numeric::NearlyEqual( Y, aSecond.Y );
    }
} // namespace ost