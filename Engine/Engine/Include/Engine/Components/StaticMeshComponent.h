// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetRef.h"
#include "Engine/Asset/Model.h"
#include "Engine/World/Component.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class IMaterialInstance;
    class SceneGraph;

    class StaticMeshComponent : public RenderComponent
    {
    public:
        void SetModel(const AssetRef<Model>& model);

    public: // Render Component
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

        void OnTransformMarkedDirty();

    private:
        AssetRef<Model> _model;
        List<ProxyHandle> _meshProxyHandles;
        SceneGraph* _pSceneGraph;
        SizeType dummyHandle = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------