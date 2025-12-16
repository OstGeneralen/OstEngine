#pragma once
#include <OstEngine/Types.h>
#include <OstEngine/Math/Vector3.h>
#include <OstEngine/Math/Matrix4x4.h>

namespace ost
{
    class CTransform
    {
    public:
        CTransform();

        CTransform& Translate( const Vector3f& aOffset );
        CTransform& Rotate( const Vector3f& aEuler );
        
        CTransform& Scale( const Float32 aFactor );
        CTransform& Scale( const Vector3f& aFactors );

        CTransform& SetPosition( const Vector3f& aPosition );
        CTransform& SetRotation( const Vector3f& aEulers );
        CTransform& SetScale( const Vector3f& aScale );

        const Vector3f& GetPosition() const;
        const Vector3f& GetRotation() const;
        const Vector3f& GetScale() const;

        const TMatrix4x4<Float32>& GetMatrix() const;
        const TMatrix4x4<Float32>& GetInverseMatrix() const;
    private:
        Vector3f _translation;
        Vector3f _rotation;
        Vector3f _scale;

        void Recalc() const;
        mutable TMatrix4x4<Float32> _matrix;
        mutable TMatrix4x4<Float32> _inverseMatrix;
        mutable bool _needsRecalc;
    };
}