// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

namespace ost
{
    class RenderComponent;
    class ActorComponent;
    class Actor;

    class IComponentInitializer
    {
    public:
        virtual ~IComponentInitializer() = default;

        virtual void InitializeAsRenderComponent(RenderComponent& component) = 0;
        virtual void DestroyAsRenderComponent(RenderComponent& component) = 0;

        virtual Actor& GetOwningActor() = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------