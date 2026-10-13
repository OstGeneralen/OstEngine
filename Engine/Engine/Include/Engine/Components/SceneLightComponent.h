// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/SceneGraph.h"

#include <Math/Color.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneLightComponent : public RenderComponent
    {
    public:
        void SetAmbientColor(const Color& color);

    public: // RenderComponent
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

    private:
        ProxyHandle _ambientLightProxyHandle;

        SceneGraph* _pSceneGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------