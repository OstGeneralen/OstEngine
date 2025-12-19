#include "OstEngine/Math/Transform.h"

#include <OstEngine/Math/NumericUtils.h>

// ------------------------------------------------------------

ost::CTransform::CTransform()
    : _translation{ 0, 0, 0 }
    , _rotation{ 0, 0, 0 }
    , _scale{ 1, 1, 1 }
{
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::Translate( const Vector3f& aOffset )
{
    _translation += aOffset;

    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::Rotate( const Vector3f& aEuler )
{
    _rotation.X = NumericUtils::ClampDegrees( _rotation.X + aEuler.X );
    _rotation.Y = NumericUtils::ClampDegrees( _rotation.Y + aEuler.Y );
    _rotation.Z = NumericUtils::ClampDegrees( _rotation.Z + aEuler.Z );

    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::Scale( const Float32 aFactor )
{
    _scale *= aFactor;

    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::Scale( const Vector3f& aFactors )
{
    _scale.X *= aFactors.X;
    _scale.Y *= aFactors.Y;
    _scale.Z *= aFactors.Z;

    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::SetPosition( const Vector3f& aPosition )
{
    _translation = aPosition;
    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::SetRotation( const Vector3f& aEulers )
{
    _rotation = aEulers;
    _rotation.X = NumericUtils::ClampDegrees( _rotation.X );
    _rotation.Y = NumericUtils::ClampDegrees( _rotation.Y );
    _rotation.Z = NumericUtils::ClampDegrees( _rotation.Z );
    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::SetScale( const Vector3f& aScale )
{
    _scale = aScale;
    _needsRecalc = true;
    return *this;
}

// ------------------------------------------------------------

const ost::Vector3f& ost::CTransform::GetPosition() const
{
    return _translation;
}

// ------------------------------------------------------------

const ost::Vector3f& ost::CTransform::GetRotation() const
{
    return _rotation;
}

// ------------------------------------------------------------

const ost::Vector3f& ost::CTransform::GetScale() const
{
    return _scale;
}

// ------------------------------------------------------------

void ost::CTransform::Recalc() const
{
    const Matrix4x4 tMat = Matrix4x4::Translation( _translation );
    const Matrix4x4 sMat = Matrix4x4::Scale( _scale );
    
    const math::Degrees xRot = _rotation.X;
    const math::Degrees yRot = _rotation.Y;
    const math::Degrees zRot = _rotation.Z;

    const Matrix3x3 rX = Matrix3x3::RotationX( xRot );
    const Matrix3x3 rY = Matrix3x3::RotationY( yRot );
    const Matrix3x3 rZ = Matrix3x3::RotationZ( zRot );
    const Matrix4x4 rMat = rX * rY * rZ;

    _matrix = sMat * rMat * tMat;
    _inverseMatrix = _matrix.GetInverse();
    _needsRecalc = false;
}

// ------------------------------------------------------------

const ost::Matrix4x4& ost::CTransform::GetMatrix() const
{
    if (_needsRecalc)
    {
        Recalc();
    }
    return _matrix;
}

// ------------------------------------------------------------

const ost::Matrix4x4& ost::CTransform::GetInverseMatrix() const
{
    if (_needsRecalc)
    {
        Recalc();
    }
    return _inverseMatrix;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------