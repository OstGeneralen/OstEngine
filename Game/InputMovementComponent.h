// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/EngineContext.h>
#include <Engine/Game/Actor.h>
#include <Engine/Game/Component.h>
#include <Engine/Game/Transform.h>
#include <Engine/System/InputReader.h>

// ------------------------------------------------------------

class InputMovementComponent : public ost::Component
{
public:
    InputMovementComponent(ost::Actor& owner)
        : ost::Component{owner}
    {
    }

    bool ShouldTick() const override
    {
        return true;
    }

    void Update(ost::EngineContext& context) override
    {
        ost::Transform& transform = GetOwner().GetTransform();

        ost::Vector3f direction{0.0f, 0.0f, 0.0f};
        Float32 rotation = 0.0f;

        if (context.GetInput().Down(ost::EKeyboard::Up))
        {
            direction.Y += 1;
        }
        if (context.GetInput().Down(ost::EKeyboard::Down))
        {
            direction.Y -= 1;
        }
        if (context.GetInput().Down(ost::EKeyboard::W))
        {
            direction.Z += 1;
        }
        if (context.GetInput().Down(ost::EKeyboard::S))
        {
            direction.Z -= 1;
        }
        if (context.GetInput().Down(ost::EKeyboard::D))
        {
            direction.X += 1;
        }
        if (context.GetInput().Down(ost::EKeyboard::A))
        {
            direction.X -= 1;
        }

        if (context.GetInput().Down(ost::EKeyboard::Left))
        {
            rotation -= 1.0f;
        }
        if (context.GetInput().Down(ost::EKeyboard::Right))
        {
            rotation += 1.0f;
        }

        const ost::Vector3f movement = direction.GetNormalized() * 2.0f * context.GetTime().deltaTime;
        transform.Move(movement, ost::ESpace::Local);
        transform.Rotate(ost::Quaternion::FromRotationAxis({0, 1, 0}, rotation * context.GetTime().deltaTime));
    }
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------