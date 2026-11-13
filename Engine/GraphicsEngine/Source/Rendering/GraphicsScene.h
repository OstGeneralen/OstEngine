// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IGraphicsScene.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/RenderMaterial.h"

#include <Container/List.h>
#include <Container/Map.h>

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
        void AddMaterial(const GraphicsSceneMaterial& material) override;
        void AddLight(const GraphicsSceneLight& light) override;
        // END IGraphicsScene

        void Clear();
        void PrepareData(const GraphicsResourceManager& resources, const Vector2f& outputDimensions);

        const RenderMaterial& GetRenderMaterial( Uint64 index ) const;
        const FrameBufferStructure& GetFrameBufferData() const;
        const List<LightsBufferStructure>& GetLightBuffersData() const;
        const List<RenderCommand>& GetRenderCommands() const;

    private:
        List<GraphicsSceneObject> _pendingObjects;
        Map<Uint64, GraphicsSceneMaterial> _pendingMaterials;
        List<LightData> _pendingLights;
        GraphicsSceneCamera _pendingCamera;

        FrameBufferStructure _frameBufferData;
        List<LightsBufferStructure> _lightBuffersData;
        List<RenderCommand> _commands;
        List<RenderMaterial> _materials;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------