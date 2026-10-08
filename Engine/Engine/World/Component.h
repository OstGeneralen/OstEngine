// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IComponentTicker.h"

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ComponentContext;
    class ComponentInitializer;

    class ActorComponent
    {
    public:
        virtual ~ActorComponent() = default;

        virtual void Initialize(ComponentInitializer& initializer);
        virtual void Destroy(ComponentInitializer& initializer);

        virtual void Start(ComponentContext& ctx);
        virtual void Update(ComponentContext& ctx);

        Actor& GetOwner();
        const Actor& GetOwner() const;

        void InitializeTicked(IComponentTicker& ticker);
        void DestroyTicked(IComponentTicker& ticker);

    protected:
        bool _shouldTick = false; // In your custom components constructor, you set this value

    private:
        TickerHandle _tickHandle;
        Actor* _pOwner = nullptr;
    };

    // ------------------------------------------------------------

    class RenderGraph;

    class RenderComponent : public ActorComponent
    {
    public:
        virtual ~RenderComponent() = default;

        virtual void Initialize(ComponentInitializer& initializer) override;
        virtual void Destroy(ComponentInitializer& initializer) override;

        virtual void InitializeRenderState(RenderGraph& renderGraph) = 0;
        virtual void DestroyRenderState(RenderGraph& renderGraph) = 0;
        virtual void UpdateDirtyTransform(RenderGraph& renderGraph) = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------