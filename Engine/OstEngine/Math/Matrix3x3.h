#pragma once
#include <OstEngine/Math/AngleUnit.h>
#include <OstEngine/Math/Matrix2x2.h>
#include <OstEngine/Math/Vector3.h>

namespace ost
{
    template <typename T>
    class TMatrix3x3
    {
    public:
        T M11, M12, M13;
        T M21, M22, M23;
        T M31, M32, M33;

    public:
        TMatrix3x3();
        TMatrix3x3( T a11, T a12, T a13, T a21, T a22, T a23, T a31, T a32, T a33 );
        TMatrix3x3( const TMatrix3x3& ) = default;

        static TMatrix3x3 RotationX( math::Radians r );
        static TMatrix3x3 RotationY( math::Radians r );
        static TMatrix3x3 RotationZ( math::Radians r );

        TMatrix3x3& Transpose();
        TMatrix3x3 GetTransposed() const;

        TMatrix3x3 GetInverse() const;

        T GetDeterminant() const;
    };

    template<typename T>
    static TVector3<T> operator*(const TVector3<T>& aVec, const TMatrix3x3<T>& aMat)
    {
        return TVector3<T>( aVec.X * aMat.M11 + aVec.Y * aMat.M21 + aVec.Z * aMat.M31,
                            aVec.X * aMat.M12 + aVec.Y * aMat.M22 + aVec.Z * aMat.M32,
                            aVec.X * aMat.M13 + aVec.Y * aMat.M23 + aVec.Z * aMat.M33 );
    }

    template <typename T>
    static TMatrix3x3<T> operator*( const TMatrix3x3<T>& aFirst, const TMatrix3x3<T>& aSecond );

    template <typename T>
    inline TMatrix3x3<T> ost::TMatrix3x3<T>::RotationX( math::Radians r )
    {
        return TMatrix3x3<T>{ 1, 0, 0, 0, cos( r.Get() ), sin( r.Get() ), 0, -sin( r.Get() ), cos( r.Get() ) };
    }

    template <typename T>
    inline TMatrix3x3<T> ost::TMatrix3x3<T>::RotationY( math::Radians r )
    {
        return TMatrix3x3<T>{ cos( r.Get() ), 0, -sin( r.Get() ), 0, 1, 0, sin( r.Get() ), 0, cos( r.Get() ) };
    }

    template <typename T>
    inline TMatrix3x3<T> ost::TMatrix3x3<T>::RotationZ( math::Radians r )
    {
        return TMatrix3x3<T>{ cos( r.Get() ), sin( r.Get() ), 0, -sin( r.Get() ), cos( r.Get() ), 0, 0, 0, 1 };
    }

    template <typename T>
    inline ost::TMatrix3x3<T>::TMatrix3x3()
        : M11{ static_cast<T>( 1 ) }
        , M22{ static_cast<T>( 1 ) }
        , M33{ static_cast<T>( 1 ) }
        , M21{ 0 }
        , M23{ 0 }
        , M31{ 0 }
        , M12{ 0 }
        , M32{ 0 }
        , M13{ 0 }
    {
    }

    template <typename T>
    inline ost::TMatrix3x3<T>::TMatrix3x3( T a11, T a12, T a13, T a21, T a22, T a23, T a31, T a32, T a33 )
        : M11{ a11 }
        , M22{ a22 }
        , M33{ a33 }
        , M21{ a21 }
        , M23{ a23 }
        , M31{ a31 }
        , M12{ a12 }
        , M32{ a32 }
        , M13{ a13 }
    {
    }

    template <typename T>
    inline TMatrix3x3<T>& ost::TMatrix3x3<T>::Transpose()
    {
        std::swap( M21, M12 );
        std::swap( M31, M13 );
        std::swap( M23, M32 );
        return *this;
    }

    template <typename T>
    inline TMatrix3x3<T> ost::TMatrix3x3<T>::GetTransposed() const
    {
        TMatrix3x3<T> tm = *this;
        return tm.Transpose();
    }

    template <typename T>
    TMatrix3x3<T> operator*( const TMatrix3x3<T>& aFirst, const TMatrix3x3<T>& aSecond )
    {
        TMatrix3x3<T> result;
        result.M11 = ( aFirst.M11 * aSecond.M11 ) + ( aFirst.M12 * aSecond.M21 ) + ( aFirst.M13 * aSecond.M31 );
        result.M21 = ( aFirst.M21 * aSecond.M11 ) + ( aFirst.M22 * aSecond.M21 ) + ( aFirst.M23 * aSecond.M31 );
        result.M31 = ( aFirst.M31 * aSecond.M11 ) + ( aFirst.M32 * aSecond.M21 ) + ( aFirst.M33 * aSecond.M31 );

        result.M12 = ( aFirst.M11 * aSecond.M12 ) + ( aFirst.M12 * aSecond.M22 ) + ( aFirst.M13 * aSecond.M32 );
        result.M22 = ( aFirst.M21 * aSecond.M12 ) + ( aFirst.M22 * aSecond.M22 ) + ( aFirst.M23 * aSecond.M32 );
        result.M32 = ( aFirst.M31 * aSecond.M12 ) + ( aFirst.M32 * aSecond.M22 ) + ( aFirst.M33 * aSecond.M32 );

        result.M13 = ( aFirst.M11 * aSecond.M13 ) + ( aFirst.M12 * aSecond.M23 ) + ( aFirst.M13 * aSecond.M33 );
        result.M23 = ( aFirst.M21 * aSecond.M13 ) + ( aFirst.M22 * aSecond.M23 ) + ( aFirst.M23 * aSecond.M33 );
        result.M33 = ( aFirst.M31 * aSecond.M13 ) + ( aFirst.M32 * aSecond.M23 ) + ( aFirst.M33 * aSecond.M33 );
        return result;
    }

    template <typename T>
    inline TMatrix3x3<T> ost::TMatrix3x3<T>::GetInverse() const
    {
        // Calculate minors
        const T minor11 = TMatrix2x2<T>( M22, M32, M23, M33 ).GetDeterminant();
        const T minor21 = TMatrix2x2<T>( M12, M32, M13, M33 ).GetDeterminant();
        const T minor31 = TMatrix2x2<T>( M12, M22, M13, M23 ).GetDeterminant();

        const T minor12 = TMatrix2x2<T>( M21, M31, M23, M33 ).GetDeterminant();
        const T minor22 = TMatrix2x2<T>( M11, M31, M13, M33 ).GetDeterminant();
        const T minor32 = TMatrix2x2<T>( M11, M21, M13, M23 ).GetDeterminant();

        const T minor13 = TMatrix2x2<T>( M21, M31, M22, M32 ).GetDeterminant();
        const T minor23 = TMatrix2x2<T>( M11, M31, M12, M32 ).GetDeterminant();
        const T minor33 = TMatrix2x2<T>( M11, M21, M12, M22 ).GetDeterminant();

        // Cofactors
        const T cofactor11 = minor11;
        const T cofactor21 = -minor21;
        const T cofactor31 = minor31;
        const T cofactor12 = -minor12;
        const T cofactor22 = minor22;
        const T cofactor32 = -minor32;
        const T cofactor13 = minor13;
        const T cofactor23 = -minor23;
        const T cofactor33 = minor33;

        // Result is the transpose of cofactors
        TMatrix3x3<T> result;
        result.M11 = cofactor11;
        result.M21 = cofactor12;
        result.M31 = cofactor13;

        result.M12 = cofactor21;
        result.M22 = cofactor22;
        result.M32 = cofactor23;

        result.M13 = cofactor31;
        result.M23 = cofactor32;
        result.M33 = cofactor33;

        const T det = ( M11 * cofactor11 ) + ( M12 * cofactor12 ) + ( M13 * cofactor13 );

        // Safety check to avoid division by zero
        if ( std::abs( det ) < static_cast<T>( 0.000001 ) )
        {
            return TMatrix3x3<T>(); // Or handle error
        }

        const T invDet = static_cast<T>( 1 ) / det;

        result.M11 *= invDet;
        result.M12 *= invDet;
        result.M13 *= invDet;
        result.M21 *= invDet;
        result.M22 *= invDet;
        result.M23 *= invDet;
        result.M31 *= invDet;
        result.M32 *= invDet;
        result.M33 *= invDet;

        return result;
    }

    template <typename T>
    inline T ost::TMatrix3x3<T>::GetDeterminant() const
    {
        const T posFactor1 = M11 * M22 * M33;
        const T posFactor2 = M21 * M32 * M13;
        const T posFactor3 = M31 * M12 * M23;

        const T negFactor1 = M11 * M32 * M23;
        const T negFactor2 = M21 * M12 * M33;
        const T negFactor3 = M31 * M22 * M13;

        return posFactor1 + posFactor2 + posFactor3 - negFactor1 - negFactor2 - negFactor3;
    }

} // namespace ost