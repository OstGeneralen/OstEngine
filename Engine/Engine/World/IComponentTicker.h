// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class ActorComponent;
    class ComponentContext;

    using TickerHandle = Uint64;

    class IComponentTicker
    {
    public:
        virtual ~IComponentTicker() = default; 

        virtual TickerHandle RegisterTicked(ActorComponent& component) = 0;
        virtual void UnregisterTicked(TickerHandle handle) = 0;

        virtual void TickAll(ComponentContext& ctx) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------