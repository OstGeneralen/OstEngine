// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/EngineContext.h"

// ------------------------------------------------------------

namespace ost
{
    class Actor;

    class Component
    {
    public:
        Component(Actor& owner)
            : _owner{&owner}
        {
        }
        virtual ~Component() = default;

        virtual bool ShouldTick() const
        {
            return false;
        }

        virtual void Start(EngineContext& context)
        {
        }
        virtual void Update(EngineContext& context)
        {
        }

        Actor& GetOwner()
        {
            return *_owner;
        }
        const Actor& GetOwner() const
        {
            return *_owner;
        }

    private:
        Actor* _owner;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------