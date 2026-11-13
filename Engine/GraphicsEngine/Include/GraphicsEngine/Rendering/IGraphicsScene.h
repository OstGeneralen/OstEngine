// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Lights.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EGraphicsSceneCameraProjection
    {
        Ortho,
        Persp,
    };

    struct GraphicsSceneCamera
    {
        EGraphicsSceneCameraProjection projectionType;
        Vector2f sizeFactors;
        Float32 yFoV;
        Float32 nearDistance = 0.001f;
        Float32 farDistance = 1000.0f;
        Matrix4x4 transform;
    };

    struct GraphicsSceneMaterial
    {
        Uint64 uid;

        EBlendMode blendMode;

        HShader vertexShader;
        HShader pixelShader;

        HUniformBuffer uniformBuffer;

        HTexture textures[8];
        SizeType numTextures;
    };

    struct GraphicsSceneObject
    {
        Uint64 materialID;

        HVertexBuffer vertexBuffer;
        HIndexBuffer indexBuffer;

        Uint64 indexOffset;
        Uint64 indexCount;
        Uint64 vertexOffset;

        Matrix4x4 transform;
    };

    struct GraphicsSceneLight
    {
        LightData data;
    };

    class IGraphicsScene
    {
    public:
        virtual void SetCamera(const GraphicsSceneCamera& camera) = 0;
        virtual void AddMaterial(const GraphicsSceneMaterial& material) = 0;
        virtual void AddObject(const GraphicsSceneObject& object) = 0;
        virtual void AddLight(const GraphicsSceneLight& light) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------