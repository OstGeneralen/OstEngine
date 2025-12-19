#pragma once
#include <OstEngine/Math/DxMath.h>
#include <OstEngine/Math/NumericUtils.h>
#include <OstEngine/Types.h>

#include <cmath>

namespace ost
{
    // ------------------------------------------------------------
    // Declaration
    // ------------------------------------------------------------
    template <typename T>
    class TVector4
    {
    public:
        using DxVecUtil = DxVecTypeUtility<T, 4>;

        // clang-format off
        union
        {
            DxVecUtil::DxVecType Vec;
            struct { T X, Y, Z, W; };
        };
        // clang-format on

    public:
        TVector4();
        TVector4( const T aX, const T aY, const T aZ, const T aW );

        TVector4( const TVector4& ) = default;
        TVector4( TVector4&& ) noexcept = default;

        TVector4& operator=( const TVector4& ) = default;
        TVector4& operator=( TVector4&& ) noexcept = default;

        template <typename TargetType>
        TVector4<TargetType> ToType() const;

        T Dot( const TVector4& aOther ) const;

        T MagnitudeSqr() const;
        T Magnitude() const;

        TVector4 GetNormalized() const;
        TVector4& Normalize();

        TVector4<T>& operator+=( const TVector4& aOther );
        TVector4<T>& operator-=( const TVector4& aOther );
        TVector4<T>& operator*=( const T aScalar );
        TVector4<T>& operator/=( const T aScalar );

        TVector4<T> operator+( const TVector4& aOther ) const;
        TVector4<T> operator-( const TVector4& aOther ) const;
        TVector4<T> operator*( const T aOther ) const;
        TVector4<T> operator/( const T aOther ) const;

        bool operator==( const TVector4& aOther ) const;
    };

    // ------------------------------------------------------------
    // Typed Vector3s
    // ------------------------------------------------------------
    using Vector4f = TVector4<Float32>;
    using Vector4i = TVector4<Int32>;
    using Vector4u = TVector4<Uint32>;
    // ------------------------------------------------------------

    // ------------------------------------------------------------
    // Begin Definition
    // ------------------------------------------------------------
    template <typename T>
    inline ost::TVector4<T>::TVector4()
        : X{ static_cast<T>( 0 ) }
        , Y{ static_cast<T>( 0 ) }
        , Z{ static_cast<T>( 0 ) }
        , W{ static_cast<T>( 0 ) }
    {
    }

    template <typename T>
    inline ost::TVector4<T>::TVector4( const T aX, const T aY, const T aZ, const T aW )
        : X{ aX }
        , Y{ aY }
        , Z{ aZ }
        , W{ aW }
    {
    }

    template <typename T>
    template <typename TargetType>
    inline TVector4<TargetType> ost::TVector4<T>::ToType() const
    {
        return TVector4<TargetType>( static_cast<TargetType>( X ), static_cast<TargetType>( Y ),
                                     static_cast<TargetType>( Z ), static_cast<TargetType>( W ) );
    }

    template <typename T>
    inline T ost::TVector4<T>::Dot( const TVector4<T>& aOther ) const
    {
        T result;
        DxVecUtil::StoreSingle( result,
                                DirectX::XMVector4Dot( DxVecUtil::ToXMVec( Vec ), DxVecUtil::ToXMVec( aOther.Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector4<T>::MagnitudeSqr() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector4LengthSq( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector4<T>::Magnitude() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector4Length( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector4<T> ost::TVector4<T>::GetNormalized() const
    {
        TVector4 result;
        DxVecUtil::Store( result.Vec, DirectX::XMVector4Normalize( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::Normalize()
    {
        DxVecUtil::Store( Vec, DirectX::XMVector4Normalize( DxVecUtil::ToXMVec( Vec ) ) );
        return *this;
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::operator+=( const TVector4& aOther )
    {
        X += aOther.X;
        Y += aOther.Y;
        Z += aOther.Z;
        W += aOther.W;
        return *this;
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::operator-=( const TVector4& aOther )
    {
        X -= aOther.X;
        Y -= aOther.Y;
        Z -= aOther.Z;
        W -= aOther.W;
        return *this;
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::operator*=( const T aScalar )
    {
        X *= aScalar;
        Y *= aScalar;
        Z *= aScalar;
        W *= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::operator/=( const T aScalar )
    {
        X /= aScalar;
        Y /= aScalar;
        Z /= aScalar;
        W /= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator+( const TVector4<T>& aSecond ) const
    {
        return TVector4<T>( X + aSecond.X, Y + aSecond.Y, Z + aSecond.Z, W + aSecond.W );
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator-( const TVector4<T>& aSecond ) const
    {
        return TVector4<T>( X - aSecond.X, Y - aSecond.Y, Z - aSecond.Z, W - aSecond.W );
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator*( const T aScalar ) const
    {
        return TVector4<T>( X * aScalar, Y * aScalar, Z * aScalar, W * aScalar );
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator/( const T aScalar ) const
    {
        return TVector4<T>( X / aScalar, Y / aScalar, Z / aScalar, W / aScalar );
    }

    template <typename T>
    inline bool TVector4<T>::operator==( const TVector4<T>& aSecond ) const
    {
        return ( X == aSecond.X ) && ( Y == aSecond.Y ) && ( Z == aSecond.Z ) && ( W == aSecond.W );
    }

    template <>
    inline bool TVector4<Float32>::operator==( const TVector4<Float32>& aSecond ) const
    {
        return NumericUtils::NearlyEqual( X, aSecond.X ) && NumericUtils::NearlyEqual( Y, aSecond.Y ) &&
               NumericUtils::NearlyEqual( Z, aSecond.Z ) && NumericUtils::NearlyEqual( W, aSecond.W );
    }
} // namespace ost