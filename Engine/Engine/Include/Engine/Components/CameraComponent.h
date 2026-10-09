// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/SceneGraph.h"

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    class CameraComponent : public RenderComponent
    {
    public:
        void MakeOrthographic(Float32 sizeFactorX, Float32 sizeFactorY);
        void MakePerspective(Float32 vFoV);

    public: // RenderComponent
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

    public:
        void ProcessTransformChanged();

    private:
        SceneGraph* _pSceneGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------