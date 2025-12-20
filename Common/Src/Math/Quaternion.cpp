#include "OstEngine/Common/Math/Quaternion.h"

// ------------------------------------------------------------

ost::CQuaternion::CQuaternion()
{
    DirectX::XMStoreFloat4( &Quat, DirectX::XMQuaternionIdentity() );
}

// ------------------------------------------------------------

ost::CQuaternion::CQuaternion( float aX, float aY, float aZ, float aW )
    : X{ aX }
    , Y{ aY }
    , Z{ aZ }
    , W{ aW }
{
}

// ------------------------------------------------------------

ost::CQuaternion& ost::CQuaternion::SetEulers( const EulerAngles& aEulers )
{
    const Vector3f eulerRad = aEulers.ToEulerVectorRadians();
    DirectX::XMStoreFloat4( &Quat, DirectX::XMQuaternionRotationRollPitchYaw( eulerRad.X, eulerRad.Y, eulerRad.Z ) );
    return *this;
}

// ------------------------------------------------------------

ost::CQuaternion ost::CQuaternion::operator*( const CQuaternion& aRhs ) const
{
    DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4( &Quat );
    DirectX::XMVECTOR q2 = DirectX::XMLoadFloat4( &aRhs.Quat );

    DirectX::XMVECTOR qr = DirectX::XMQuaternionMultiply( q1, q2 );

    ost::CQuaternion result;
    DirectX::XMStoreFloat4( &result.Quat, qr );

    return result;
}

// ------------------------------------------------------------

ost::CQuaternion& ost::CQuaternion::operator*=( const CQuaternion& aRhs )
{
    DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4( &Quat );
    DirectX::XMVECTOR q2 = DirectX::XMLoadFloat4( &aRhs.Quat );

    DirectX::XMVECTOR qr = DirectX::XMQuaternionMultiply( q1, q2 );

    DirectX::XMStoreFloat4( &Quat, qr );

    return *this;
}

// ------------------------------------------------------------

ost::Vector3f ost::operator*( const Vector3f& aV, const CQuaternion& aQ )
{
    DirectX::XMVECTOR v = DirectX::XMLoadFloat3( &( aV.Vec ) );
    DirectX::XMVECTOR q = DirectX::XMLoadFloat4( &( aQ.Quat ) );
    DirectX::XMVECTOR r = DirectX::XMVector3Rotate( v, q );

    Vector3f result;
    DirectX::XMStoreFloat3( &result.Vec, r );
    return result;
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::CQuaternion::ToRotationMatrix() const
{
    DirectX::XMVECTOR q = DirectX::XMLoadFloat4( &Quat );
    ost::Matrix3x3 rm;
    DirectX::XMStoreFloat3x3( &( rm.Mat ), DirectX::XMMatrixRotationQuaternion( q ) );
    return rm;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------