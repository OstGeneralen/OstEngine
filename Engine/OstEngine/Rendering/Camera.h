#pragma once
#include <OstEngine/Common/Math/Vector2.h>
#include <OstEngine/Common/Math/Transform.h>
#include <OstEngine/Common/Math/Matrix4x4.h>
#include <OstEngine/Common/Math/AngleUnit.h>

namespace ost
{
    class CCamera
    {
    public:
        CTransform Transform;

        void InitializeOrthographic( const Vector2f& aSize );
        void InitializePerspective( Float32 aAspect, Radians aFov );

        Matrix4x4 GetViewProjection() const;

    private:
        Matrix4x4 _projectionMatrix;
    };
}