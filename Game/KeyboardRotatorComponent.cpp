// Kasper "OstGeneralen" Esbjornsson - 2026
#include "KeyboardRotatorComponent.h"

#include "Engine/IOstEngine.h"

#include <Engine/World/Actor.h>
#include <Math/Quaternion.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

KeyboardRotatorComponent::KeyboardRotatorComponent()
    : _input{ost::pEngine->GetServiceLocator().GetRequired<ost::IInputReader>()}
{
    AddFlag(ost::EComponentFlag::Ticked);
}

void KeyboardRotatorComponent::Update(Float32 deltaTime)
{
    ost::Vector3f rotation;

    if (_input.Down(ost::EKeyboard::Right))
    {
        rotation.Y -= 1.0f;
    }
    if (_input.Down(ost::EKeyboard::Left))
    {
        rotation.Y += 1.0f;
    }
    if (_input.Down(ost::EKeyboard::Up))
    {
        rotation.X -= 1.0f;
    }
    if (_input.Down(ost::EKeyboard::Down))
    {
        rotation.X += 1.0f;
    }

    if (rotation.MagnitudeSq() > 0)
    {
        const auto n = rotation.GetNormalized();
        const Float32 speed = 45.0f * deltaTime * ost::math::DegToRad;

        const ost::Quaternion pitch = ost::Quaternion::FromRotationAxis({1, 0, 0}, n.X * speed);
        const ost::Quaternion yaw = ost::Quaternion::FromRotationAxis({0, 1, 0}, n.Y * speed);

        GetOwner().transform.Rotate(yaw, ost::ESpace::World);
        GetOwner().transform.Rotate(pitch);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------