#pragma once
#include "OstEngine/Common/Math/AngleUnit.h"
#include "OstEngine/Common/Math/Vector3.h"

#include <OstEngine/Common/Math/DxMath/DirectXMath.h>

namespace ost
{
    class Matrix3x3
    {
    public:
        union {
            DirectX::XMFLOAT3X3 Mat;
            struct
            {
                Float32 M11, M12, M13;
                Float32 M21, M22, M23;
                Float32 M31, M32, M33;
            };
        };

    public:
        Matrix3x3();
        Matrix3x3( Float32 a11, Float32 a12, Float32 a13, Float32 a21, Float32 a22, Float32 a23, Float32 a31,
                   Float32 a32, Float32 a33 );
        Matrix3x3( const Matrix3x3& ) = default;

        static Matrix3x3 RotationX( Radians r );
        static Matrix3x3 RotationY( Radians r );
        static Matrix3x3 RotationZ( Radians r );

        Matrix3x3& Transpose();
        Matrix3x3 GetTransposed() const;

        Matrix3x3 GetInverse() const;

        Float32 GetDeterminant() const;

        Matrix3x3 operator*( const Matrix3x3& aRhs ) const;
    };

    static Vector3f operator*( const Vector3f& aV, const Matrix3x3& aM );

} // namespace ost