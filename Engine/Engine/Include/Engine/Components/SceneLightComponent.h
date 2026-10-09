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
        void SetSunDirection(const Vector3f& direction);
        void SetAmbientColor(const Color& color);

    public: // RenderComponent
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;

    private:
        Vector3f _sunDirection = Vector3f{0.0f, -1.0f, 0.0f};
        Color _ambientColor = Color{0.0f, 0.05f, 0.09f, 1.0f};

        ProxyHandle _directionalLightProxyHandle;
        ProxyHandle _ambientLightProxyHandle;

        SceneGraph* _pSceneGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------