#pragma once
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
        T X;
        T Y;
        T Z;
        T W;

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
    };

    // ------------------------------------------------------------
    // Typed Vector3s
    // ------------------------------------------------------------
    using Vector4f = TVector4<Float32>;
    using Vector4d = TVector4<Float64>;
    using Vector4i = TVector4<Int32>;
    using Vector4u = TVector4<Uint32>;
    // ------------------------------------------------------------

    template <typename T>
    static TVector4<T> operator+( const TVector4<T>& aFirst, const TVector4<T>& aSecond );

    template <typename T>
    static TVector4<T> operator-( const TVector4<T>& aFirst, const TVector4<T>& aSecond );

    template <typename T>
    static TVector4<T> operator*( const TVector4<T>& aVector, const T aScalar );

    template <typename T>
    static TVector4<T> operator/( const TVector4<T>& aVector, const T aScalar );

    template <typename T>
    static bool operator==( const TVector4<T>& aFirst, const TVector4<T>& aSecond );

    template <>
    static bool operator==( const TVector4<Float32>& aFirst, const TVector4<Float32>& aSecond );

    template <>
    static bool operator==( const TVector4<Float64>& aFirst, const TVector4<Float64>& aSecond );

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
    inline T ost::TVector4<T>::Dot( const TVector4& aOther ) const
    {
        return ( X * aOther.X ) + ( Y * aOther.Y ) + ( Z * aOther.Z ) + ( W * aOther.W );
    }

    template <typename T>
    inline T ost::TVector4<T>::MagnitudeSqr() const
    {
        return ( X * X ) + ( Y * Y ) + ( Z * Z ) + ( W * W );
    }

    template <typename T>
    inline T ost::TVector4<T>::Magnitude() const
    {
        return sqrt( MagnitudeSqr() );
    }

    template <typename T>
    inline TVector4<T> ost::TVector4<T>::GetNormalized() const
    {
        const T magnitude = Magnitude();
        if ( magnitude == static_cast<T>( 0 ) )
        {
            return TVector4<T>();
        }
        else
        {
            return TVector4<T>( X, Y, Z, W ) / magnitude;
        }
    }

    template <typename T>
    inline TVector4<T>& ost::TVector4<T>::Normalize()
    {
        const T magnitude = Magnitude();
        if ( magnitude > static_cast<T>( 0 ) )
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
            W /= magnitude;
        }
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
    TVector4<T> operator+( const TVector4<T>& aFirst, const TVector4<T>& aSecond )
    {
        return TVector4<T>( aFirst.X + aSecond.X, aFirst.Y + aSecond.Y, aFirst.Z + aSecond.Z, aFirst.W + aSecond.W );
    }

    template <typename T>
    TVector4<T> operator-( const TVector4<T>& aFirst, const TVector4<T>& aSecond )
    {
        return TVector4<T>( aFirst.X - aSecond.X, aFirst.Y - aSecond.Y, aFirst.Z - aSecond.Z, aFirst.W - aSecond.W );
    }

    template <typename T>
    TVector4<T> operator*( const TVector4<T>& aVector, const T aScalar )
    {
        return TVector4<T>( aVector.X * aScalar, aVector.Y * aScalar, aVector.Z * aScalar, aVector.W * aScalar );
    }

    template <typename T>
    TVector4<T> operator/( const TVector4<T>& aVector, const T aScalar )
    {
        return TVector4<T>( aVector.X / aScalar, aVector.Y / aScalar, aVector.Z / aScalar, aVector.W / aScalar );
    }

    template <typename T>
    bool operator==( const TVector4<T>& aFirst, const TVector4<T>& aSecond )
    {
        return ( aFirst.X == aSecond.X ) && ( aFirst.Y == aSecond.Y ) && ( aFirst.Z == aSecond.Z ) &&
               ( aFirst.W == aSecond.W );
    }

    template <>
    bool operator==( const TVector4<Float32>& aFirst, const TVector4<Float32>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y ) &&
               NumericUtils::NearlyEqual( aFirst.Z, aSecond.Z ) && NumericUtils::NearlyEqual( aFirst.W, aSecond.W );
    }

    template <>
    bool operator==( const TVector4<Float64>& aFirst, const TVector4<Float64>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y ) &&
               NumericUtils::NearlyEqual( aFirst.Z, aSecond.Z ) && NumericUtils::NearlyEqual( aFirst.W, aSecond.W );
    }

} // namespace ost