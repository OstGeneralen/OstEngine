// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneViewCamera.h"

#include <GraphicsEngine/Rendering/IRenderQueue.h>
#include <GraphicsEngine/Rendering/IRenderer.h>

using namespace ost;

// ------------------------------------------------------------

void ost::SceneViewCamera::Move(const Vector3f& offset)
{
    _position += offset;
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