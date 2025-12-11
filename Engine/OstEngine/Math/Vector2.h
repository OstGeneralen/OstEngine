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
    class TVector2
    {
    public:
        T X;
        T Y;

    public:
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
    };

    template <typename T>
    static TVector2<T> operator+( const TVector2<T>& aFirst, const TVector2<T>& aSecond );

    template <typename T>
    static TVector2<T> operator-( const TVector2<T>& aFirst, const TVector2<T>& aSecond );

    template <typename T>
    static TVector2<T> operator*( const TVector2<T>& aVector, const T aScalar );

    template <typename T>
    static TVector2<T> operator/( const TVector2<T>& aVector, const T aScalar );

    template <typename T>
    static bool operator==( const TVector2<T>& aFirst, const TVector2<T>& aSecond );

    template <>
    static bool operator==( const TVector2<Float32>& aFirst, const TVector2<Float32>& aSecond );

    template <>
    static bool operator==( const TVector2<Float64>& aFirst, const TVector2<Float64>& aSecond );

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
        return ( X * aOther.X ) + ( Y * aOther.Y );
    }

    template <typename T>
    inline T ost::TVector2<T>::MagnitudeSqr() const
    {
        return ( X * X ) + ( Y * Y );
    }

    template <typename T>
    inline T ost::TVector2<T>::Magnitude() const
    {
        return sqrt( MagnitudeSqr() );
    }

    template <typename T>
    inline TVector2<T> ost::TVector2<T>::GetNormalized() const
    {
        const T magnitude = Magnitude();
        if ( magnitude == static_cast<T>( 0 ) )
        {
            return TVector2<T>();
        }
        else
        {
            return TVector2<T>( X, Y ) / magnitude;
        }
    }

    template <typename T>
    inline TVector2<T>& ost::TVector2<T>::Normalize()
    {
        const T magnitude = Magnitude();
        if ( magnitude > static_cast<T>( 0 ) )
        {
            X /= magnitude;
            Y /= magnitude;
        }
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
    TVector2<T> operator+( const TVector2<T>& aFirst, const TVector2<T>& aSecond )
    {
        return TVector2<T>( aFirst.X + aSecond.X, aFirst.Y + aSecond.Y );
    }

    template <typename T>
    TVector2<T> operator-( const TVector2<T>& aFirst, const TVector2<T>& aSecond )
    {
        return TVector2<T>( aFirst.X - aSecond.X, aFirst.Y - aSecond.Y );
    }

    template <typename T>
    TVector2<T> operator*( const TVector2<T>& aVector, const T aScalar )
    {
        return TVector2<T>( aVector.X * aScalar, aVector.Y * aScalar );
    }

    template <typename T>
    TVector2<T> operator/( const TVector2<T>& aVector, const T aScalar )
    {
        return TVector2<T>( aVector.X / aScalar, aVector.Y / aScalar );
    }

    template <typename T>
    bool operator==( const TVector2<T>& aFirst, const TVector2<T>& aSecond )
    {
        return ( aFirst.X == aSecond.X ) && ( aFirst.Y == aSecond.Y );
    }

    template <>
    bool operator==( const TVector2<Float32>& aFirst, const TVector2<Float32>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y );
    }

    template <>
    bool operator==( const TVector2<Float64>& aFirst, const TVector2<Float64>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y );
    }

} // namespace ost