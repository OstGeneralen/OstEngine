// Kasper "OstGeneralen" Esbjornsson - 2026
#include "KeyboardMovementComponent.h"

#include <Engine/IOstEngine.h>
#include <Engine/World/Actor.h>
#include <Math/Quaternion.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

KeyboardMovementComponent::KeyboardMovementComponent()
    : _input{ost::pEngine->GetServiceLocator().GetRequired<ost::IInputReader>()}
{
    AddFlag(ost::EComponentFlag::Ticked);
}

void KeyboardMovementComponent::Update(Float32 deltaTime)
{
    ost::Vector3f rotation;
    ost::Vector3f direction;

    if (_input.Down(ost::EKeyboard::W))
    {
        direction.Z += 1;
    }
    if (_input.Down(ost::EKeyboard::S))
    {
        direction.Z -= 1;
    }
    if (_input.Down(ost::EKeyboard::D))
    {
        direction.X += 1;
    }
    if (_input.Down(ost::EKeyboard::A))
    {
        direction.X -= 1;
    }
    if (_input.Down(ost::EKeyboard::Space))
    {
        direction.Y += 1;
    }
    if (_input.Down(ost::EKeyboard::LCtrl))
    {
        direction.Y -= 1;
    }

    if (_input.Down(ost::EKeyboard::E))
    {
        rotation.Y += 1;
    }
    if (_input.Down(ost::EKeyboard::Q))
    {
        rotation.Y -= 1;
    }

    direction.Normalize();

    GetOwner().transform.Move(direction * 2.0f * deltaTime);

    if (rotation.MagnitudeSq() > 0.0f)
    {
        GetOwner().transform.Rotate(ost::Quaternion::FromRotationAxis(rotation, 3.141f * deltaTime));
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------