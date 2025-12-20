#pragma once
#include <OstEngine/Common/Math/DxMath/DirectXMath.h>
#include <OstEngine/Common/Math/Vector3.h>
#include <OstEngine/Common/Math/Vector4.h>
#include <OstEngine/Common/Math/AngleUnit.h>
#include <OstEngine/Common/Math/Matrix3x3.h>


namespace ost
{
	class CQuaternion
	{
    public:
		// clang-format off
		union
		{
            DirectX::XMFLOAT4 Quat;
            struct { float X, Y, Z, W; };
		};
		// clang-format on

		CQuaternion();
        CQuaternion( float aX, float aY, float aZ, float aW );
        CQuaternion( const Vector3f& aEuler );
        CQuaternion( const CQuaternion& ) = default;
        CQuaternion( CQuaternion&& ) noexcept = default;

		CQuaternion& operator=( const CQuaternion& ) = default; 

		CQuaternion& SetEulers( const EulerAngles& aEulers );
		CQuaternion operator*( const CQuaternion& aRhs ) const;
        CQuaternion& operator*=( const CQuaternion& aRhs );

		Matrix3x3 ToRotationMatrix() const;
	};

	static Vector3f operator*(const Vector3f& aV, const CQuaternion& aQ)
	{
        DirectX::XMVECTOR v = DirectX::XMLoadFloat3( &( aV.Vec ) );
        DirectX::XMVECTOR q = DirectX::XMLoadFloat4( &( aQ.Quat ) );
        DirectX::XMVECTOR r = DirectX::XMVector3Rotate( v, q );

        Vector3f result;
        DirectX::XMStoreFloat3( &result.Vec, r );
        return result;
	}
}