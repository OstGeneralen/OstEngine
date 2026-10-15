// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/SceneGraph.h"

#include <Math/Color.h>

// ------------------------------------------------------------

namespace ost
{
    class LightComponent : public RenderComponent
    {
    public:
        virtual ~LightComponent() = default;

        void SetColor(const Color& color);
        const Color& GetColor() const;

        void SetIntensity(Float32 intensity);
        Float32 GetIntensity() const;

        // BEGIN RenderComponent
        void InitializeRenderState(SceneGraph& SceneGraph) override;
        void DestroyRenderState(SceneGraph& SceneGraph) override;
        void UpdateDirtyTransform(SceneGraph& SceneGraph) override;
        // END RenderComponent

    protected:
        virtual void InitializeLightType(LightRenderProxy& proxy) = 0;

        LightRenderProxy& GetProxy() const;

    private:
        void NotifyTransformChanged();

        SceneGraph* _pSceneGraph;
        ProxyHandle _proxyHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------