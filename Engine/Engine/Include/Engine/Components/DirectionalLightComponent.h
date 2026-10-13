// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/SceneGraph.h"

// ------------------------------------------------------------

namespace ost
{
    class DirectionalLightComponent : public RenderComponent
    {
    public:
        DirectionalLightComponent();

        void SetColor(const Color& color, Float32 intensity = 1.0f);

        // BEGIN RenderComponent
        void Initialize(IComponentInitializer& initializer) override;

        void InitializeRenderState(SceneGraph& sceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;
        // END RenderComponent

        void OnTransformDirty();

    private:
        SceneGraph* _pSceneGraph;
        ProxyHandle _hSceneProxy;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------