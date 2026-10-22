// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneViewCamera.h"

#include <GraphicsEngine/Rendering/IRenderQueue.h>
#include <GraphicsEngine/Rendering/IRenderer.h>

using namespace ost;

// ------------------------------------------------------------

void ost::SceneViewCamera::Move(const Vector3f& offset)
{
    const Vector3f fwd = _rotation.RotateVector({0, 0, 1});
    const Vector3f rgt = _rotation.RotateVector({1, 0, 0});
    const Vector3f up = {0, 1, 0};

    _position += ((fwd * offset.Z) + (rgt * offset.X) + (up * offset.Y));
}

void ost::SceneViewCamera::LookLeftRight(Float32 lookDegrees)
{
    _lookDegrees.Y += lookDegrees;
    _lookDegrees.Y = math::Clamp(_lookDegrees.Y, -80.0f, 80.0f);

    ost::Quaternion yaw = Quaternion::FromEulersDegrees(0, _lookDegrees.Y, 0);
    ost::Quaternion pitch = Quaternion::FromEulersDegrees(_lookDegrees.X, 0, 0);
    _rotation = pitch * yaw;
}

void ost::SceneViewCamera::LookUpDown(Float32 lookDegrees)
{
    _lookDegrees.X += lookDegrees;

    if (_lookDegrees.X >= 360.0f)
    {
        _lookDegrees.X -= 360.0f;
    }
    else if (_lookDegrees.X <= -360.0f)
    {
        _lookDegrees.X += 360.0f;
    }

    ost::Quaternion yaw = Quaternion::FromEulersDegrees(0, _lookDegrees.Y, 0);
    ost::Quaternion pitch = Quaternion::FromEulersDegrees(_lookDegrees.X, 0, 0);
    _rotation = pitch * yaw;
}

// ------------------------------------------------------------

void ost::SceneViewCamera::InjectToRenderQueue(IRenderQueue& renderQueue, IRenderer& renderer)
{
    Matrix4x4 view = Matrix4x4::CreateTransformMatrix(_position, _rotation).GetInverse();
    Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(90.0f * math::DegToRad, renderer.GetAspectRatio(), 0.01f, 100.0f);
    Matrix4x4 viewProjection = view * projection;
    renderQueue.SetView(viewProjection, view.GetInverse());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------