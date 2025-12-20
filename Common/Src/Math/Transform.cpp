#include "OstEngine/Common/Math/Transform.h"

#include <OstEngine/Common/Math/AngleUnit.h>
#include <OstEngine/Common/Utility/NumericUtils.h>

// ------------------------------------------------------------

ost::CTransform::CTransform()
    : _translation{ 0, 0, 0 }
    , _rotation{}
    , _scale{ 1, 1, 1 }
{
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::Move( const Vector3f& aMove )
{
    return Translate( aMove );
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
    CQuaternion rBy = CQuaternion().SetEulers( EulerAngles( Degrees( aEuler.X),  Degrees(aEuler.Y), Degrees(aEuler.Z)));
    _rotation *= rBy;

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
    _rotation.SetEulers( EulerAngles( Degrees( aEulers.X ), Degrees( aEulers.Y ), Degrees( aEulers.Z ) ) );
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

const ost::CQuaternion& ost::CTransform::GetRotation() const
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
    const Matrix4x4 rMat = _rotation.ToRotationMatrix();

    _matrix = sMat * rMat * tMat;
    _inverseMatrix = _matrix.GetInverse();
    _needsRecalc = false;
}

// ------------------------------------------------------------

const ost::Matrix4x4& ost::CTransform::GetMatrix() const
{
    if ( _needsRecalc )
    {
        Recalc();
    }
    return _matrix;
}

// ------------------------------------------------------------

const ost::Matrix4x4& ost::CTransform::GetInverseMatrix() const
{
    if ( _needsRecalc )
    {
        Recalc();
    }
    return _inverseMatrix;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------