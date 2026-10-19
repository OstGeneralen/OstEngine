// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorCamera.h"

#include "EditorContext.h"

#include <Engine/EngineContext.h>
#include <Math/Math.h>

using namespace ost;

// ------------------------------------------------------------

void EditorCamera::Resize(const Vector2u& resolution)
{
    const Vector2f fResolution = resolution.VectorCast<Float32>();
    const Float32 aspect = fResolution.X / fResolution.Y;
    _projection = Matrix4x4::CreatePerspectiveProjection(60.0f * math::DegToRad, aspect, 0.1f, 100.0f);
}

void EditorCamera::Update()
{
    const Float32 deltaTime = EngineContext::Get().Time().deltaTime;
    const auto& input = EditorContext::Get().coreEngine.GetInputReader();

    Vector3f moveDir = {0, 0, 0};

    if (input.Down(EKeyboard::W))
    {
        moveDir.Z += 1.0f;
    }
    else if (input.Down(EKeyboard::S))
    {
        moveDir.Z -= 1.0f;
    }
    if (input.Down(EKeyboard::D))
    {
        moveDir.X += 1.0f;
    }
    else if (input.Down(EKeyboard::A))
    {
        moveDir.X -= 1.0f;
    }

    const Vector3f movement = moveDir.GetNormalized() * deltaTime * _moveSpeed;
    Vector3f newPos = _transform.GetPosition();
    newPos = newPos + (_transform.GetForward() * movement.Z) + (_transform.GetRight() * movement.X);
    _transform.SetPosition(newPos);

    const Matrix4x4 view = _transform.GetWorldTransform().GetInverse();
    EditorContext::Get().graphicsEngine.GetRenderQueue().SetView(view * _projection, _transform.GetWorldTransform());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------