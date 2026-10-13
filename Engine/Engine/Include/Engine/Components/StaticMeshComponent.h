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
        void SetModel(HModel model);
        void SetModel(const std::string& modelName);

        void SetMaterial(HMaterialInstance material);
        void SetMaterial(const std::string& materialName);

    public: // Render Component
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

        void OnTransformMarkedDirty();

    private:
        SceneGraph* _pSceneGraph;
        ProxyHandle _proxyMeshHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------