// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Objects/Buffer.h"
#include "Objects/Texture.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderScene;
    class GraphicsResourceManager;
    class RenderHardwareInterface;

    class SceneRenderer
    {
    public:
        SceneRenderer();

        void InitializeResources(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);

        void Resize(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);

        void ExecuteRenderScene(const RenderScene& scene, const RenderHardwareInterface& rhi);

        void BlitOutputToTarget(const Texture& target const RenderHardwareInterface& rhi);

    private:
        void InitializeBuffers(const RenderHardwareInterface& rhi);
        void InitializeTextures(const RenderHardwareInterface& rhi, const Vector2u& renderDimensions);

        void ExecuteGeometryPass(const RenderScene& scene, const RenderHardwareInterface& rhi);
        void ExecuteLightPass(const RenderScene& scene, const RenderHardwareInterface& rhi);

        Vector2u _renderSize;

        Buffer _frameBuffer;
        Buffer _lightBuffer;
        Buffer _objectBuffer;

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