#include "OstEngine/Rendering/Camera.h"

// ------------------------------------------------------------

void ost::CCamera::InitializeOrthographic( const Vector2f& aSize )
{

    const float halfX = aSize.X * 0.5f;
    const float halfY = aSize.Y * 0.5f;

    _projectionMatrix = Matrix4x4::OrthographicProjection( { -halfX, -halfY, 0.001f }, { halfX, halfY, 100.0f } );
}

// ------------------------------------------------------------

void ost::CCamera::InitializePerspective( Float32 aAspect, math::Radians aFov )
{
    _projectionMatrix = Matrix4x4::PerspectiveProjection( aAspect, aFov, 0.001f, 100.0f );
}

// ------------------------------------------------------------

ost::Matrix4x4 ost::CCamera::GetViewProjection() const
{
    auto viewMat = Transform.GetInverseMatrix();

    return  viewMat * _projectionMatrix;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------