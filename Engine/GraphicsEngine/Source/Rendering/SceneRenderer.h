// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/ISceneRenderer.h"
#include "Objects/Buffer.h"
#include "Objects/Texture.h"
#include "Rendering/PipelineState.h"
#include "Rendering/GraphicsScene.h"

// ------------------------------------------------------------

namespace ost
{
    class GraphicsScene;
    class GraphicsResourceManager;
    class RenderHardwareInterface;

    class SceneRenderer : public ISceneRenderer
    {
    public:
        SceneRenderer();

        void InitializeResources(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);
        void Resize(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);

        void ClearGraphicsScene();
        void ExecuteGraphicsScene(const GraphicsScene& scene, const RenderHardwareInterface& rhi);
        void BlitOutputToTarget(const Texture& target, const RenderHardwareInterface& rhi);

        // BEGIN ISceneRenderer
        const ITexture* GetTargetTexture(ESceneRendererTargetTexture t) const override;
        // END ISceneRenderer

    private:
        void InitializeBuffers(const RenderHardwareInterface& rhi);
        void InitializeTextures(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);

        void ExecuteGeometryPass(const GraphicsScene& scene, const RenderHardwareInterface& rhi);
        void ExecuteLightPass(const GraphicsScene& scene, const RenderHardwareInterface& rhi);

        Buffer _frameBuffer;
        Buffer _lightBuffer;
        Buffer _objectBuffer;

        PipelineState _geometryPassPipelineState;
        PipelineState _lightPassPipelineState;

        Texture _gbufferAlbedo; // Target for scene material albedos
        Texture _gbufferNormal; // Target for scene material normals
        Texture _gbufferORM;    // Target for scene material ORMs
        Texture _gbufferDepth;  // Target for scene depth
        Texture _outputTexture; // Target for the light/output pass
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------