#pragma once
#include <OstEngine/Common/Math/Matrix4x4.h>
#include <OstEngine/Common/Math/Vector3.h>
#include <OstEngine/Common/Math/Quaternion.h>
#include <OstEngine/Types.h>

namespace ost
{
    class CTransform
    {
    public:
        CTransform();

        CTransform& Move( const Vector3f& aMove );
        CTransform& Translate( const Vector3f& aOffset );
        
        CTransform& RotateAround( const Vector3f& aWorldPoint, const Vector3f& aEuler );
        CTransform& Rotate( const Vector3f& aEuler );
        CTransform& Rotate( const CQuaternion& aQuat );

        CTransform& Scale( const Float32 aFactor );
        CTransform& Scale( const Vector3f& aFactors );

        CTransform& SetPosition( const Vector3f& aPosition );
        CTransform& SetRotation( const CQuaternion& aQuat );
        CTransform& SetRotation( const Vector3f& aEulers );
        CTransform& SetScale( const Vector3f& aScale );

        const Vector3f& GetPosition() const;
        const CQuaternion& GetRotation() const;
        const Vector3f& GetScale() const;

        const Matrix4x4& GetMatrix() const;
        const Matrix4x4& GetInverseMatrix() const;

        // Move point from this transforms space into outer space
        Vector3f TransformPoint( const Vector3f& aP ) const;

        // Move direction from this transforms space into outer space
        Vector3f TransformDirection( const Vector3f& aD ) const;
        
        // Move point from outer space into this transforms space
        Vector3f InverseTransformPoint( const Vector3f& aP ) const;

        // Move direction from outer space into this transforms space
        Vector3f InverseTransformDirection( const Vector3f& aD ) const;

    private:
        Vector3f _translation;
        Vector3f _scale;
        CQuaternion _rotation;

        void Recalc() const;

        // Mutable members to allow recalculation upon calls to Get
        mutable Matrix4x4 _matrix;
        mutable Matrix4x4 _inverseMatrix;
        mutable bool _needsRecalc;
    };
} // namespace ost