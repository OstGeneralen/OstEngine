// Kasper "OstGeneralen" Esbjornsson - 2026
#include "KeyboardMovementComponent.h"

#include <Engine/World/Actor.h>
#include <Engine/World/ComponentContext.h>
#include <Math/Quaternion.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

KeyboardMovementComponent::KeyboardMovementComponent()
{
    _shouldTick = true;
}

void KeyboardMovementComponent::Update(ost::ComponentContext& context)
{
    ost::Vector3f rotation;
    ost::Vector3f direction;

    if (context.Input().Down(ost::EKeyboard::W))
    {
        direction.Z += 1;
    }
    if (context.Input().Down(ost::EKeyboard::S))
    {
        direction.Z -= 1;
    }
    if (context.Input().Down(ost::EKeyboard::D))
    {
        direction.X += 1;
    }
    if (context.Input().Down(ost::EKeyboard::A))
    {
        direction.X -= 1;
    }
    if (context.Input().Down(ost::EKeyboard::Space))
    {
        direction.Y += 1;
    }
    if (context.Input().Down(ost::EKeyboard::LCtrl))
    {
        direction.Y -= 1;
    }

    if (context.Input().Down(ost::EKeyboard::Right))
    {
        rotation.Y += 1;
    }
    if (context.Input().Down(ost::EKeyboard::Left))
    {
        rotation.Y -= 1;
    }

    direction.Normalize();

    GetOwner().transform.Move(direction * 2.0f * context.Time().deltaTime);

    if (rotation.MagnitudeSq() > 0.0f)
    {
        GetOwner().transform.Rotate(ost::Quaternion::FromRotationAxis(rotation, 3.141f * context.Time().deltaTime));
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------