#include "OstEngine/Rendering/Camera.h"

// ------------------------------------------------------------

void ost::CCamera::InitializeOrthographic( const Vector2f& aSize )
{

    const float halfX = aSize.X * 0.5f;
    const float halfY = aSize.Y * 0.5f;

    _projectionMatrix = TMatrix4x4<float>::OrthographicProjection( { -halfX, -halfY, 0.001f }, { halfX, halfY, 1.0f } );
}

// ------------------------------------------------------------

void ost::CCamera::InitializePerspective( Float32 aAspect, math::Radians aFov )
{
    _projectionMatrix = TMatrix4x4<float>::PerspectiveProjection( aAspect, aFov, 0.001f, 1.0f );
}

// ------------------------------------------------------------

ost::TMatrix4x4<float> ost::CCamera::GetViewProjection() const
{
    return Transform.GetMatrix() * _projectionMatrix;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------