// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderScene.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderCommand.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsResourceManager;

    class RenderScene : public IRenderScene
    {
    public:
        // BEGIN IRenderScene
        void SetCamera(const RenderSceneCamera& camera) override;
        void AddObject(const RenderSceneObject& object) override;
        void AddLight(const RenderSceneLight& light) override;
        // END IRenderScene

        void PrepareData(const GraphicsResourceManager& resources, const Vector2f& outputDimensions);

        const FrameBufferStructure& GetFrameBufferData() const;
        const List<LightsBufferStructure>& GetLightBuffersData() const;
        const List<RenderCommand>& GetRenderCommands() const;

    private:
        List<RenderSceneObject> _pendingObjects;
        List<LightData> _pendingLights;
        RenderSceneCamera _pendingCamera;

        FrameBufferStructure _frameBufferData;
        List<LightsBufferStructure> _lightBuffersData;
        List<RenderCommand> _commands;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------