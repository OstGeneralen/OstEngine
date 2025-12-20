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
    class TVector3
    {
    public:
        using DxVecUtil = DxVecTypeUtility<T, 3>;

        // clang-format off
        union
        {
            DxVecUtil::DxVecType Vec;
            struct { T X, Y, Z; };
        };
        // clang-format on

    public:
        TVector3();
        TVector3( const T aX, const T aY, const T aZ );

        TVector3( const TVector3& ) = default;
        TVector3( TVector3&& ) noexcept = default;

        TVector3& operator=( const TVector3& ) = default;
        TVector3& operator=( TVector3&& ) noexcept = default;

        template <typename TargetType>
        TVector3<TargetType> ToType() const;

        T Dot( const TVector3& aOther ) const;
        TVector3 Cross( const TVector3& aOther ) const;

        T MagnitudeSqr() const;
        T Magnitude() const;

        TVector3 GetNormalized() const;
        TVector3& Normalize();

        TVector3<T>& operator+=( const TVector3& aOther );
        TVector3<T>& operator-=( const TVector3& aOther );
        TVector3<T>& operator*=( const T aScalar );
        TVector3<T>& operator/=( const T aScalar );

        TVector3<T> operator+( const TVector3<T>& aOther ) const;
        TVector3<T> operator-( const TVector3<T>& aOther ) const;
        TVector3<T> operator*( const T aOther ) const;
        TVector3<T> operator/( const T aOther ) const;

        bool operator==( const TVector3<T>& aOther ) const;
    };

    // ------------------------------------------------------------
    // Typed Vector3s
    // ------------------------------------------------------------
    using Vector3f = TVector3<Float32>;
    using Vector3i = TVector3<Int32>;
    using Vector3u = TVector3<Uint32>;
    // ------------------------------------------------------------

    // ------------------------------------------------------------
    // Begin Definition
    // ------------------------------------------------------------
    template <typename T>
    inline ost::TVector3<T>::TVector3()
        : X{ static_cast<T>( 0 ) }
        , Y{ static_cast<T>( 0 ) }
        , Z{ static_cast<T>( 0 ) }
    {
    }

    template <typename T>
    inline ost::TVector3<T>::TVector3( const T aX, const T aY, const T aZ )
        : X{ aX }
        , Y{ aY }
        , Z{ aZ }
    {
    }

    template <typename T>
    template <typename TargetType>
    inline TVector3<TargetType> ost::TVector3<T>::ToType() const
    {
        return TVector3<TargetType>( static_cast<TargetType>( X ), static_cast<TargetType>( Y ),
                                     static_cast<TargetType>( Z ) );
    }

    template <typename T>
    inline T ost::TVector3<T>::Dot( const TVector3& aOther ) const
    {
        T result;
        DxVecUtil::StoreSingle( result,
                          DirectX::XMVector3Dot( DxVecUtil::ToXMVec( Vec ), DxVecUtil::ToXMVec( aOther.Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector3<T> ost::TVector3<T>::Cross( const TVector3& aOther ) const
    {
        TVector3 result;
        DxVecUtil::Store( result.Vec,
                          DirectX::XMVector3Cross( DxVecUtil::ToXMVec( Vec ), DxVecUtil::ToXMVec( aOther.Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector3<T>::MagnitudeSqr() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector3LengthSq( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline T ost::TVector3<T>::Magnitude() const
    {
        T result;
        DxVecUtil::StoreSingle( result, DirectX::XMVector3Length( DxVecUtil::ToXMVec( Vec ) ) );
        return result;
    }

    template <typename T>
    inline TVector3<T> ost::TVector3<T>::GetNormalized() const
    {
        TVector3 result;
        DxVecUtil::Store(result.Vec,  DirectX::XMVector3Normalize( DxVecUtil::ToXMVec( Vec ) ));
        return result;
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::Normalize()
    {
        DxVecUtil::Store( Vec, DirectX::XMVector3Normalize( DxVecUtil::ToXMVec( Vec ) ) );
        return *this;
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::operator+=( const TVector3& aOther )
    {
        X += aOther.X;
        Y += aOther.Y;
        Z += aOther.Z;
        return *this;
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::operator-=( const TVector3& aOther )
    {
        X -= aOther.X;
        Y -= aOther.Y;
        Z -= aOther.Z;
        return *this;
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::operator*=( const T aScalar )
    {
        X *= aScalar;
        Y *= aScalar;
        Z *= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::operator/=( const T aScalar )
    {
        X /= aScalar;
        Y /= aScalar;
        Z /= aScalar;
        return *this;
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator+( const TVector3<T>& aSecond ) const
    {
        return TVector3<T>( X + aSecond.X, Y + aSecond.Y, Z + aSecond.Z );
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator-( const TVector3<T>& aSecond ) const
    {
        return TVector3<T>( X - aSecond.X, Y - aSecond.Y, Z - aSecond.Z );
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator*( const T aScalar ) const
    {
        return TVector3<T>( X * aScalar, Y * aScalar, Z * aScalar );
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator/( const T aScalar ) const
    {
        return TVector3<T>( X / aScalar, Y / aScalar, Z / aScalar );
    }

    template <typename T>
    inline bool TVector3<T>::operator==( const TVector3<T>& aSecond ) const
    {
        return ( X == aSecond.X ) && ( Y == aSecond.Y ) && ( Z == aSecond.Z );
    }

    template <>
    inline bool TVector3<Float32>::operator==( const TVector3<Float32>& aSecond ) const
    {
        return util::numeric::NearlyEqual( X, aSecond.X ) && util::numeric::NearlyEqual( Y, aSecond.Y ) &&
               util::numeric::NearlyEqual( Z, aSecond.Z );
    }
} // namespace ost