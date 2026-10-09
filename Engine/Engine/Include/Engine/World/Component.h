// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// clang-format off
#define OPTIONAL_COMPONENT_METHOD {}
// clang-format on

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ComponentContext;
    class IComponentInitializer;
    class IAssetManager;
    class ComponentTicker;

    // ------------------------------------------------------------

    enum class EComponentFlag : Uint32
    {
        None = 0,
        Ticked = 1 << 0,     // Update will be invoked each frame on this component
        AssetOwner = 1 << 1, // Load will be invoked on this component
        All = 0xFFFFFFFF,
    };

    // ------------------------------------------------------------

    class ActorComponent
    {
    public:
        virtual ~ActorComponent() = default;

        virtual void Initialize(IComponentInitializer& initializer);
        virtual void Destroy(IComponentInitializer& initializer);

        // Load/Unload will only be called if the "AssetOwner" flag is set
        virtual void Load(IAssetManager& assetManager) OPTIONAL_COMPONENT_METHOD;
        virtual void Unload(IAssetManager& assetManager) OPTIONAL_COMPONENT_METHOD;

        // Start & Update are only called if the "Ticked" flag is set
        virtual void Start(ComponentContext& ctx) OPTIONAL_COMPONENT_METHOD;
        virtual void Update(ComponentContext& ctx) OPTIONAL_COMPONENT_METHOD;

        Actor& GetOwner();
        const Actor& GetOwner() const;

        void InitializeTicked(ComponentTicker& ticker);
        void DestroyTicked(ComponentTicker& ticker);

    protected:
        void AddFlag(EComponentFlag flag);

    private:
        bool HasFlag(EComponentFlag flag) const;

    private:
        EComponentFlag _flags = EComponentFlag::None;
        Actor* _pOwner = nullptr;
        Uint64 _tickHandle;
    };

    // ------------------------------------------------------------

    class SceneGraph;

    class RenderComponent : public ActorComponent
    {
    public:
        virtual ~RenderComponent() = default;

        virtual void Initialize(IComponentInitializer& initializer) override;
        virtual void Destroy(IComponentInitializer& initializer) override;

        virtual void InitializeRenderState(SceneGraph& SceneGraph) = 0;
        virtual void DestroyRenderState(SceneGraph& SceneGraph) = 0;
        virtual void UpdateDirtyTransform(SceneGraph& SceneGraph) = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------