#pragma once
#include <OstEngine/Math/Vector2.h>
#include <OstEngine/Math/Transform.h>
#include <OstEngine/Math/Matrix4x4.h>
#include <OstEngine/Math/AngleUnit.h>

namespace ost
{
    class CCamera
    {
    public:
        CTransform Transform;

        void InitializeOrthographic( const Vector2f& aSize );
        void InitializePerspective( Float32 aAspect, math::Radians aFov );

    private:
        TMatrix4x4<float> _projectionMatrix;
    };
}