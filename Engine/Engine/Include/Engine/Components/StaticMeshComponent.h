// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/SceneGraph.h"

#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class StaticMeshComponent : public RenderComponent
    {
    public:
        StaticMeshComponent( ModelHandle modelHandle );

    public: // Render Component
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

        void OnTransformMarkedDirty();
    private:
        SceneGraph* _pSceneGraph;
        ModelHandle _modelHandle;
        ProxyHandle _proxyMeshHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------