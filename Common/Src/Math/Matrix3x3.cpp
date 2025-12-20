#include "OstEngine/Common/Math/Matrix3x3.h"

// ------------------------------------------------------------

ost::Matrix3x3::Matrix3x3()
    : M11{ 1.f }
    , M12{ 0.f }
    , M13{ 0.f }
    , M21{ 0.f }
    , M22{ 1.f }
    , M23{ 0.f }
    , M31{ 0.f }
    , M32{ 0.f }
    , M33{ 1.f }
{
}

// ------------------------------------------------------------

ost::Matrix3x3::Matrix3x3( Float32 a11, Float32 a12, Float32 a13, Float32 a21, Float32 a22, Float32 a23, Float32 a31,
                           Float32 a32, Float32 a33 )
    : M11{ a11 }
    , M12{ a12 }
    , M13{ a13 }
    , M21{ a21 }
    , M22{ a22 }
    , M23{ a23 }
    , M31{ a31 }
    , M32{ a32 }
    , M33{ a33 }

{
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::Matrix3x3::GetInverse() const
{
    DirectX::XMMATRIX matrix = DirectX::XMLoadFloat3x3( &Mat );
    DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant( DirectX::XMLoadFloat3x3( &Mat ) );

    ost::Matrix3x3 result;
    DirectX::XMStoreFloat3x3( &result.Mat, DirectX::XMMatrixInverse( &det, matrix ) );
    return result;
}

// ------------------------------------------------------------

Float32 ost::Matrix3x3::GetDeterminant() const
{
    DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant( DirectX::XMLoadFloat3x3( &Mat ) );

    Float32 result;
    DirectX::XMStoreFloat( &result, det );
    return result;
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::Matrix3x3::RotationX( Radians r )
{
    DirectX::XMMATRIX mat = DirectX::XMMatrixRotationX( r.Get() );
    Matrix3x3 result;
    DirectX::XMStoreFloat3x3( &( result.Mat ), mat );
    return result;
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::Matrix3x3::RotationY( Radians r )
{
    DirectX::XMMATRIX mat = DirectX::XMMatrixRotationY( r.Get() );
    Matrix3x3 result;
    DirectX::XMStoreFloat3x3( &( result.Mat ), mat );
    return result;
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::Matrix3x3::RotationZ( Radians r )
{
    DirectX::XMMATRIX mat = DirectX::XMMatrixRotationZ( r.Get() );
    Matrix3x3 result;
    DirectX::XMStoreFloat3x3( &( result.Mat ), mat );
    return result;
}

// ------------------------------------------------------------

ost::Matrix3x3 ost::Matrix3x3::operator*( const Matrix3x3& aRhs ) const
{
    DirectX::XMMATRIX m1 = DirectX::XMLoadFloat3x3( &( Mat ) );
    DirectX::XMMATRIX m2 = DirectX::XMLoadFloat3x3( &( aRhs.Mat ) );
    DirectX::XMMATRIX r = DirectX::XMMatrixMultiply( m1, m2 );
    Matrix3x3 result;
    DirectX::XMStoreFloat3x3( &( result.Mat ), r );
    return result;
}

// ------------------------------------------------------------

ost::Vector3f ost::operator*( const Vector3f& aV, const Matrix3x3& aM )
{
    DirectX::XMVECTOR v = DirectX::XMLoadFloat3( &( aV.Vec ) );
    DirectX::XMMATRIX m = DirectX::XMLoadFloat3x3( &( aM.Mat ) );

    DirectX::XMVECTOR rv = DirectX::XMVector3Transform( v, m );
    Vector3f r;
    DirectX::XMStoreFloat3( &( r.Vec ), rv );
    return r;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------