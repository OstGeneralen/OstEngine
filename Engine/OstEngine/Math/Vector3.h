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
    class TVector3
    {
    public:
        T X;
        T Y;
        T Z;

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
    };

    template <typename T>
    static TVector3<T> operator+( const TVector3<T>& aFirst, const TVector3<T>& aSecond );

    template <typename T>
    static TVector3<T> operator-( const TVector3<T>& aFirst, const TVector3<T>& aSecond );

    template <typename T>
    static TVector3<T> operator*( const TVector3<T>& aVector, const T aScalar );

    template <typename T>
    static TVector3<T> operator/( const TVector3<T>& aVector, const T aScalar );

    template <typename T>
    static bool operator==( const TVector3<T>& aFirst, const TVector3<T>& aSecond );

    template <>
    static bool operator==( const TVector3<Float32>& aFirst, const TVector3<Float32>& aSecond );

    template <>
    static bool operator==( const TVector3<Float64>& aFirst, const TVector3<Float64>& aSecond );

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
        return ( X * aOther.X ) + ( Y * aOther.Y ) + ( Z * aOther.Z );
    }

    template<typename T>
    inline TVector3<T> ost::TVector3<T>::Cross(const TVector3& aOther) const
    {
        const T cx = ( Y * aOther.Z ) - ( Z * aOther.Y );
        const T cy = ( Z * aOther.X ) - ( X * aOther.Z );
        const T cz = ( X * aOther.Y ) - ( Y * aOther.X );
        return TVector3<T>{ cx, cy, cz };
    }

    template <typename T>
    inline T ost::TVector3<T>::MagnitudeSqr() const
    {
        return ( X * X ) + ( Y * Y ) + ( Z * Z );
    }

    template <typename T>
    inline T ost::TVector3<T>::Magnitude() const
    {
        return sqrt( MagnitudeSqr() );
    }

    template <typename T>
    inline TVector3<T> ost::TVector3<T>::GetNormalized() const
    {
        const T magnitude = Magnitude();
        if ( magnitude == static_cast<T>( 0 ) )
        {
            return TVector3<T>();
        }
        else
        {
            return TVector3<T>( X, Y, Z ) / magnitude;
        }
    }

    template <typename T>
    inline TVector3<T>& ost::TVector3<T>::Normalize()
    {
        const T magnitude = Magnitude();
        if ( magnitude > static_cast<T>( 0 ) )
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
        }
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
    TVector3<T> operator+( const TVector3<T>& aFirst, const TVector3<T>& aSecond )
    {
        return TVector3<T>( aFirst.X + aSecond.X, aFirst.Y + aSecond.Y, aFirst.Z + aSecond.Z );
    }

    template <typename T>
    TVector3<T> operator-( const TVector3<T>& aFirst, const TVector3<T>& aSecond )
    {
        return TVector3<T>( aFirst.X - aSecond.X, aFirst.Y - aSecond.Y, aFirst.Z - aSecond.Z );
    }

    template <typename T>
    TVector3<T> operator*( const TVector3<T>& aVector, const T aScalar )
    {
        return TVector3<T>( aVector.X * aScalar, aVector.Y * aScalar, aVector.Z * aScalar );
    }

    template <typename T>
    TVector3<T> operator/( const TVector3<T>& aVector, const T aScalar )
    {
        return TVector3<T>( aVector.X / aScalar, aVector.Y / aScalar, aVector.Z / aScalar );
    }

    template <typename T>
    bool operator==( const TVector3<T>& aFirst, const TVector3<T>& aSecond )
    {
        return ( aFirst.X == aSecond.X ) && ( aFirst.Y == aSecond.Y ) && ( aFirst.Z == aSecond.Z );
    }

    template <>
    bool operator==( const TVector3<Float32>& aFirst, const TVector3<Float32>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y ) &&
               NumericUtils::NearlyEqual( aFirst.Z, aSecond.Z );
    }

    template <>
    bool operator==( const TVector3<Float64>& aFirst, const TVector3<Float64>& aSecond )
    {
        return NumericUtils::NearlyEqual( aFirst.X, aSecond.X ) && NumericUtils::NearlyEqual( aFirst.Y, aSecond.Y ) &&
               NumericUtils::NearlyEqual( aFirst.Z, aSecond.Z );
    }

} // namespace ost