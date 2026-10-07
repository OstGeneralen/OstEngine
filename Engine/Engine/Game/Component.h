// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

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

        virtual void Created()
        {
        }
        virtual void Update(Float32 deltaTime)
        {
        }

        Actor& GetOwner()
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