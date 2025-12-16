#pragma once
#include <OstEngine/Math/Matrix3x3.h>
#include <OstEngine/Math/Vector4.h>
#include <OstEngine/Math/Vector3.h>
#include <OstEngine/Math/AngleUnit.h>

namespace ost
{
    template <typename T>
    class TMatrix4x4
    {
    public:
        T M11, M21, M31, M41;
        T M12, M22, M32, M42;
        T M13, M23, M33, M43;
        T M14, M24, M34, M44;

    public:
        TMatrix4x4();
        TMatrix4x4( const TMatrix4x4& ) = default;
        TMatrix4x4( const TMatrix3x3<T>& aM33 );

        TMatrix4x4& Transpose();
        TMatrix4x4 GetTransposed() const;

        TMatrix4x4 GetInverse() const;

        static TMatrix4x4 Translation( const TVector3<T>& aTranslation );
        static TMatrix4x4 Scale( const TVector3<T>& aTranslation );

        static TMatrix4x4 OrthographicProjection( const TVector3<T>& aMin, const TVector3<T>& aMax );
        static TMatrix4x4 PerspectiveProjection( T aAspect, math::Radians aFov, T aNearPlaneDistance, T aFarPlaneDistance );
    };

    template <typename T>
    static TMatrix4x4<T> operator*( const TMatrix4x4<T>& aFirst, const TMatrix4x4<T>& aSecond );

    template <typename T>
    static TVector4<T> operator*( const TMatrix4x4<T>& aMat, const TVector4<T>& aVec );

    // clang-format off
    template <typename T>
    inline ost::TMatrix4x4<T>::TMatrix4x4()
        : M11{ 1 }, M21{ 0 }, M31{ 0 }, M41{ 0 }
        , M12{ 0 }, M22{ 1 }, M32{ 0 }, M42{ 0 }
        , M13{ 0 }, M23{ 0 }, M33{ 1 }, M43{ 0 }
        , M14{ 0 }, M24{ 0 }, M34{ 0 }, M44{ 1 }
    // clang-format on
    {
    }

    // clang-format off
    template <typename T>
    inline ost::TMatrix4x4<T>::TMatrix4x4( const TMatrix3x3<T>& aM33 )
        : M11{ aM33.M11 }, M21{ aM33.M21 }, M31{ aM33.M31 }, M41{ 0 }
        , M12{ aM33.M12 }, M22{ aM33.M22 }, M32{ aM33.M32 }, M42{ 0 }
        , M13{ aM33.M13 }, M23{ aM33.M23 }, M33{ aM33.M33 }, M43{ 0 }
        , M14{ 0 }, M24{ 0 }, M34{ 0 }, M44{ 1 }
    // clang-format on
    {
    }

    template <typename T>
    inline TMatrix4x4<T>& ost::TMatrix4x4<T>::Transpose()
    {
        std::swap( M21, M12 );
        std::swap( M31, M13 );
        std::swap( M41, M14 );
        std::swap( M32, M23 );
        std::swap( M42, M24 );
        std::swap( M43, M34 );
        return *this;
    }

    template <typename T>
    inline TMatrix4x4<T> ost::TMatrix4x4<T>::GetTransposed() const
    {
        TMatrix4x4<T> tm = *this;
        return tm.Transpose();
    }

    template <typename T>
    TMatrix4x4<T> operator*( const TMatrix4x4<T>& aFirst, const TMatrix4x4<T>& aSecond )
    {
        // clang-format off
        TMatrix4x4<T> result;
        result.M11 = ( aFirst.M11 * aSecond.M11 ) + ( aFirst.M21 * aSecond.M12 ) + ( aFirst.M31 * aSecond.M13 ) + ( aFirst.M41 * aSecond.M14 );
        result.M21 = ( aFirst.M11 * aSecond.M21 ) + ( aFirst.M21 * aSecond.M22 ) + ( aFirst.M31 * aSecond.M23 ) + ( aFirst.M41 * aSecond.M24 );
        result.M31 = ( aFirst.M11 * aSecond.M31 ) + ( aFirst.M21 * aSecond.M32 ) + ( aFirst.M31 * aSecond.M33 ) + ( aFirst.M41 * aSecond.M34 );
        result.M41 = ( aFirst.M11 * aSecond.M41 ) + ( aFirst.M21 * aSecond.M42 ) + ( aFirst.M31 * aSecond.M43 ) + ( aFirst.M41 * aSecond.M44 );

        result.M12 = ( aFirst.M12 * aSecond.M11 ) + ( aFirst.M22 * aSecond.M12 ) + ( aFirst.M32 * aSecond.M13 ) + ( aFirst.M42 * aSecond.M14 );
        result.M22 = ( aFirst.M12 * aSecond.M21 ) + ( aFirst.M22 * aSecond.M22 ) + ( aFirst.M32 * aSecond.M23 ) + ( aFirst.M42 * aSecond.M24 );
        result.M32 = ( aFirst.M12 * aSecond.M31 ) + ( aFirst.M22 * aSecond.M32 ) + ( aFirst.M32 * aSecond.M33 ) + ( aFirst.M42 * aSecond.M34 );
        result.M42 = ( aFirst.M12 * aSecond.M41 ) + ( aFirst.M22 * aSecond.M42 ) + ( aFirst.M32 * aSecond.M43 ) + ( aFirst.M42 * aSecond.M44 );

        result.M13 = ( aFirst.M13 * aSecond.M11 ) + ( aFirst.M23 * aSecond.M12 ) + ( aFirst.M33 * aSecond.M13 ) + ( aFirst.M43 * aSecond.M14 );
        result.M23 = ( aFirst.M13 * aSecond.M21 ) + ( aFirst.M23 * aSecond.M22 ) + ( aFirst.M33 * aSecond.M23 ) + ( aFirst.M43 * aSecond.M24 );
        result.M33 = ( aFirst.M13 * aSecond.M31 ) + ( aFirst.M23 * aSecond.M32 ) + ( aFirst.M33 * aSecond.M33 ) + ( aFirst.M43 * aSecond.M34 );
        result.M43 = ( aFirst.M13 * aSecond.M41 ) + ( aFirst.M23 * aSecond.M42 ) + ( aFirst.M33 * aSecond.M43 ) + ( aFirst.M43 * aSecond.M44 );

        result.M14 = ( aFirst.M14 * aSecond.M11 ) + ( aFirst.M24 * aSecond.M12 ) + ( aFirst.M34 * aSecond.M13 ) + ( aFirst.M44 * aSecond.M14 );
        result.M24 = ( aFirst.M14 * aSecond.M21 ) + ( aFirst.M24 * aSecond.M22 ) + ( aFirst.M34 * aSecond.M23 ) + ( aFirst.M44 * aSecond.M24 );
        result.M34 = ( aFirst.M14 * aSecond.M31 ) + ( aFirst.M24 * aSecond.M32 ) + ( aFirst.M34 * aSecond.M33 ) + ( aFirst.M44 * aSecond.M34 );
        result.M44 = ( aFirst.M14 * aSecond.M41 ) + ( aFirst.M24 * aSecond.M42 ) + ( aFirst.M34 * aSecond.M43 ) + ( aFirst.M44 * aSecond.M44 );
        // clang-format on
        return result;
    }

    template<typename T>
    ost::TMatrix4x4<T> ost::TMatrix4x4<T>::GetInverse() const
    {
        const TMatrix3x3<T> m33PartInverse = TMatrix3x3<T>( M11, M21, M31, M12, M22, M32, M13, M23, M33 ).GetInverse();
        TMatrix4x4<T> result{m33PartInverse};
        const TVector3<T> inverseTranslation = TVector3<T>{M14, M24, M34} * m33PartInverse;
        result.M14 = -inverseTranslation.X;
        result.M24 = -inverseTranslation.Y;
        result.M34 = -inverseTranslation.Z;
        return result;
    }
    
    template <typename T>
    ost::TVector4<T> operator*( const TMatrix4x4<T>& aMat, const TVector4<T>& aVec )
    {
        TVector4<T> result;
        result.X = ( aVec.X * aMat.M11 ) + ( aVec.Y * aMat.M12 ) + ( aVec.Z * aMat.M13 ) + ( aVec.W * aMat.M14 );
        result.Y = ( aVec.X * aMat.M21 ) + ( aVec.Y * aMat.M22 ) + ( aVec.Z * aMat.M23 ) + ( aVec.W * aMat.M24 );
        result.Z = ( aVec.X * aMat.M31 ) + ( aVec.Y * aMat.M32 ) + ( aVec.Z * aMat.M33 ) + ( aVec.W * aMat.M34 );
        result.W = ( aVec.X * aMat.M41 ) + ( aVec.Y * aMat.M42 ) + ( aVec.Z * aMat.M43 ) + ( aVec.W * aMat.M44 );
        return result;
    }

    template <typename T>
    inline ost::TMatrix4x4<T> ost::TMatrix4x4<T>::OrthographicProjection( const TVector3<T>& aMin, const TVector3<T>& aMax )
    {
        TMatrix4x4<T> mat;

        mat.M11 = static_cast<T>( 2 ) / ( aMax.X - aMin.X );
        mat.M22 = static_cast<T>( 2 ) / ( aMax.Y - aMin.Y );
        mat.M33 = static_cast<T>( 2 ) / ( aMax.Z - aMin.Z );

        mat.M14 = -( ( aMax.X + aMin.X ) / ( aMax.X - aMin.X ) );
        mat.M24 = -( ( aMax.Y + aMin.Y ) / ( aMax.Y - aMin.Y ) );
        mat.M34 = -( ( aMax.Z + aMin.Z ) / ( aMax.Z - aMin.Z ) );

        return mat;
    }

    template <typename T>
    inline TMatrix4x4<T> ost::TMatrix4x4<T>::PerspectiveProjection( T aAspect, math::Radians aFOV, T aNearPlaneDistance,
                                                                 T aFarPlaneDistance )
    {
        TMatrix4x4<T> mat;

        const T focalLength = static_cast<T>( 1 ) / static_cast<T>(tan( aFOV.Get() / 2.0f));
        const T Q = aFarPlaneDistance / ( aFarPlaneDistance - aNearPlaneDistance );

        mat.M11 = focalLength / aAspect;
        mat.M22 = focalLength;
        mat.M33 = Q;
        mat.M43 = static_cast<T>( 1 );
        mat.M34 = -( aNearPlaneDistance * Q );

        return mat;
    }

    template <typename T>
    inline ost::TMatrix4x4<T> ost::TMatrix4x4<T>::Translation( const TVector3<T>& aTranslation )
    {
        TMatrix4x4<T> mat;
        mat.M14 = aTranslation.X;
        mat.M24 = aTranslation.Y;
        mat.M34 = aTranslation.Z;
        return mat;
    }

    template <typename T>
    inline TMatrix4x4<T> ost::TMatrix4x4<T>::Scale( const TVector3<T>& aScale )
    {
        TMatrix4x4<T> mat;
        mat.M11 = aScale.X;
        mat.M22 = aScale.Y;
        mat.M33 = aScale.Z;
        return mat;
    }

} // namespace ost