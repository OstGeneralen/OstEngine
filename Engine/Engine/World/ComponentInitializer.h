// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IComponentTicker.h"

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ActorComponent;
    class RenderComponent;
    class RenderGraph;

    class ComponentInitializer
    {
    public:
        ComponentInitializer(Actor& ownerActor, RenderGraph& renderGraph, IComponentTicker& ticker);

        void InitializeAsRenderComponent(RenderComponent& renderComponent);
        void DestroyAsRenderComponent(RenderComponent& renderComponent);

        void InitializeAsTickedComponent(ActorComponent& tickedComponent);
        void DestroyAsTickedComponent(ActorComponent& tickedComponent);

        Actor& GetOwningActor(); 

    private:
        Actor& _ownerActor;

        RenderGraph& _renderGraph;
        IComponentTicker& _ticker;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------