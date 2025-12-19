#include <OstEngine/Math/Matrix4x4.h>

ost::Matrix4x4::Matrix4x4()
{ 
    DirectX::XMMATRIX m = DirectX::XMMatrixIdentity();
    DirectX::XMStoreFloat4x4( &Mat, m );
}

ost::Matrix4x4::Matrix4x4( const Matrix3x3& aMat3 )
    : M11{aMat3.M11}
    , M12{aMat3.M12}
    , M13{aMat3.M13}
    , M14{0.0f}
    , M21{ aMat3.M21 }
    , M22{ aMat3.M22 }
    , M23{ aMat3.M23 }
    , M24{ 0.0f }
    , M31{ aMat3.M31 }
    , M32{ aMat3.M32 }
    , M33{ aMat3.M33 }
    , M34{ 0.0f }
    , M41{ 0.0f }
    , M42{ 0.0f }
    , M43{ 0.0f }
    , M44{ 1.0f }
{
}

ost::Matrix4x4 ost::Matrix4x4::GetInverse() const
{
    DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4( &Mat );
    DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant( matrix );
    DirectX::FXMMATRIX inverse = DirectX::XMMatrixInverse( &det, matrix );
    Matrix4x4 result;
    DirectX::XMStoreFloat4x4( &( result.Mat ), inverse );
    return result;
}

ost::Matrix4x4& ost::Matrix4x4::Transpose()
{
    DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4( &Mat );
    DirectX::XMMATRIX tmatrix = DirectX::XMMatrixTranspose( matrix );
    DirectX::XMStoreFloat4x4( &Mat, tmatrix );
    return *this;
}

ost::Matrix4x4 ost::Matrix4x4::Translation( const Vector3f& aTranslation )
{
    Matrix4x4 m;
    m.M41 = aTranslation.X;
    m.M42 = aTranslation.Y;
    m.M43 = aTranslation.Z;
    return m;
}

ost::Matrix4x4 ost::Matrix4x4::Scale( const Vector3f& aScale)
{
    Matrix4x4 m;
    m.M11 = aScale.X;
    m.M22 = aScale.Y;
    m.M33 = aScale.Z;
    return m;
}

ost::Matrix4x4 ost::Matrix4x4::GetTransposed() const
{
    Matrix4x4 t = *this;
    t.Transpose();
    return t;
}

ost::Matrix4x4 ost::Matrix4x4::operator*( const Matrix4x4& aRhs ) const
{
    DirectX::XMMATRIX m1 = DirectX::XMLoadFloat4x4( &Mat );
    DirectX::XMMATRIX m2 = DirectX::XMLoadFloat4x4( &(aRhs.Mat) );
    DirectX::XMMATRIX mm = DirectX::XMMatrixMultiply( m1, m2 );

    Matrix4x4 result;
    DirectX::XMStoreFloat4x4( &( result.Mat ), mm );
    return result;
}

ost::Matrix4x4 ost::Matrix4x4::OrthographicProjection( const Vector3f& aMin, const Vector3f& aMax )
{
    const Vector3f size = aMax - aMin;

    Matrix4x4 projMat;
    DirectX::XMMATRIX matrix =
        DirectX::XMMatrixOrthographicLH( size.X, size.Y, aMin.Z, aMax.Z);
    DirectX::XMStoreFloat4x4( &( projMat.Mat ), matrix );
    return projMat;
}

ost::Matrix4x4 ost::Matrix4x4::PerspectiveProjection( Float32 aAspect, math::Radians aFov, Float32 aNearPlaneDistance,
                                                 Float32 aFarPlaneDistance )
{
    Matrix4x4 projMat;
    DirectX::XMMATRIX matrix =
        DirectX::XMMatrixPerspectiveFovLH( aFov.Get(), aAspect, aNearPlaneDistance, aFarPlaneDistance );
    DirectX::XMStoreFloat4x4( &( projMat.Mat ), matrix );
    return projMat;
}

ost::Vector4f ost::operator*( const Vector4f& aV, const Matrix4x4& aM )
{
    DirectX::XMVECTOR v = DirectX::XMLoadFloat4( &( aV.Vec ) );
    DirectX::XMMATRIX m = DirectX::XMLoadFloat4x4( &( aM.Mat ) );

    DirectX::XMVECTOR rv = DirectX::XMVector4Transform( v, m );
    Vector4f r;
    DirectX::XMStoreFloat4( &( r.Vec ), rv );
    
    return r;
}