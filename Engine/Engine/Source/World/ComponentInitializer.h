// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IComponentInitializer.h"

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ActorComponent;
    class RenderComponent;
    class SceneGraph;
    class IAssetManager;
    class ComponentTicker;

    class ComponentInitializer : public IComponentInitializer
    {
    public:
        ComponentInitializer(Actor& ownerActor, SceneGraph& sceneGraph, ComponentTicker& ticker);

        void InitializeAsTickedComponent(ActorComponent& tickedComponent);
        void DestroyAsTickedComponent(ActorComponent& tickedComponent);

        void RequestLoad(ActorComponent& component);
        void RequestUnload(ActorComponent& component);

    public: // IComponentInitializer
        void InitializeAsRenderComponent(RenderComponent& renderComponent) override;
        void DestroyAsRenderComponent(RenderComponent& renderComponent) override;

        Actor& GetOwningActor() override;

    private:
        Actor& _ownerActor;

        IAssetManager* _pAssetManager;
        SceneGraph& _SceneGraph;
        ComponentTicker& _ticker;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------