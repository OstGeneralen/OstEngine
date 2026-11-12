// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IGraphicsScene.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderCommand.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsResourceManager;

    class GraphicsScene : public IGraphicsScene
    {
    public:
        // BEGIN IGraphicsScene
        void SetCamera(const GraphicsSceneCamera& camera) override;
        void AddObject(const GraphicsSceneObject& object) override;
        void AddLight(const GraphicsSceneLight& light) override;
        // END IGraphicsScene

        void Clear();
        void PrepareData(const GraphicsResourceManager& resources, const Vector2f& outputDimensions);

        const FrameBufferStructure& GetFrameBufferData() const;
        const List<LightsBufferStructure>& GetLightBuffersData() const;
        const List<RenderCommand>& GetRenderCommands() const;

    private:
        List<GraphicsSceneObject> _pendingObjects;
        List<LightData> _pendingLights;
        GraphicsSceneCamera _pendingCamera;

        FrameBufferStructure _frameBufferData;
        List<LightsBufferStructure> _lightBuffersData;
        List<RenderCommand> _commands;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------