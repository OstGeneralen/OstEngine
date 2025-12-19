#pragma once
#include <OstEngine/Math/AngleUnit.h>
#include <OstEngine/Math/DxMath/DirectXMath.h>
#include <OstEngine/Math/Vector3.h>
#include <OstEngine/Math/Vector4.h>
#include <OstEngine/Math/Matrix3x3.h>

namespace ost
{
    class Matrix4x4
    {
    public:
        union {
            DirectX::XMFLOAT4X4 Mat;
            struct
            {
                Float32 M11, M12, M13, M14;
                Float32 M21, M22, M23, M24;
                Float32 M31, M32, M33, M34;
                Float32 M41, M42, M43, M44;
            };
        };

    public:
        Matrix4x4();
        Matrix4x4( const Matrix4x4& ) = default;
        Matrix4x4( const Matrix3x3& aMat3 );

        Matrix4x4& Transpose();
        Matrix4x4 GetTransposed() const;

        Matrix4x4 GetInverse() const;

        static Matrix4x4 Translation( const Vector3f& aTranslation );
        static Matrix4x4 Scale( const Vector3f& aTranslation );

        static Matrix4x4 OrthographicProjection( const Vector3f& aMin, const Vector3f& aMax );
        static Matrix4x4 PerspectiveProjection( Float32 aAspect, math::Radians aFov, Float32 aNearPlaneDistance,
                                                 Float32 aFarPlaneDistance );
        
        Matrix4x4 operator*( const Matrix4x4& aRhs ) const;
    };

    static Vector4f operator*( const Vector4f& aV, const Matrix4x4& aM );
} // namespace ost