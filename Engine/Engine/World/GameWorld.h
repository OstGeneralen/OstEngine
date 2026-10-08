// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/ComponentContext.h"
#include "Engine/World/ComponentTicker.h"
#include "Engine/World/RenderGraph.h"
#include "Engine/World/WorldContext.h"

// ------------------------------------------------------------

namespace ost
{
    class GameWorld : public WorldContext
    {
    public:
        GameWorld();
        ~GameWorld();

        void Tick(ComponentContext& context);
        const RenderGraph& GetRenderGraph() const;

    public:
        void RegisterComponent(Actor& actor, ActorComponent& component) override;
        void UnregisterComponent(Actor& actor, ActorComponent& component) override;

    private:
        ComponentTicker _ticker;
        RenderGraph _renderGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------