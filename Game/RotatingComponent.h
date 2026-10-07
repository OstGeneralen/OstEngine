// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/EngineContext.h>
#include <Engine/Game/Actor.h>
#include <Engine/Game/Component.h>

// ------------------------------------------------------------

class RotatingComponent : public ost::Component
{
public:
    RotatingComponent(ost::Actor& owner)
        : ost::Component{owner}
    {
    }

    bool ShouldTick() const override
    {
        return true;
    }

    void Update(ost::EngineContext& context) override
    {
        auto rotation = ost::Vector3f{1.0f, 1.0f, 1.0f};
        rotation.Normalize();
        GetOwner().GetTransform().Rotate(ost::Quaternion::FromRotationAxis(rotation, 0.5f * context.GetTime().deltaTime));
    }
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------