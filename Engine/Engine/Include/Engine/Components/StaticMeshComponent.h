// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"

#include <GraphicsEngine/Materials/IMaterialInstance.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class IMaterialInstance;
    class SceneGraph;

    class StaticMeshComponent : public RenderComponent
    {
    public:
        void SetModel(HModel model);

        void SetMaterial(HMaterialInstance material, Uint32 index = 0);

        HMaterialInstance GetMaterialHandle(Uint32 index = 0);

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