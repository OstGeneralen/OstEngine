// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Lights.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    enum class ERenderSceneCameraProjection
    {
        Ortho,
        Persp,
    };

    struct RenderSceneCamera
    {
        ERenderSceneCameraProjection projectionType;
        Vector2f sizeFactors;
        Float32 yFoV;
        Float32 nearDistance = 0.001f;
        Float32 farDistance = 1000.0f;
        Matrix4x4 transform;
    };

    struct RenderSceneObject
    {
        HVertexBuffer vertexBuffer;
        HIndexBuffer indexBuffer;

        HShader vertexShader;
        HShader pixelShader;

        Uint64 indexOffset;
        Uint64 indexCount;
        Uint64 vertexOffset;

        Matrix4x4 transform;
    };

    struct RenderSceneLight
    {
        LightData data;
    };

    class IRenderScene
    {
    public:
        virtual void SetCamera(const RenderSceneCamera& camera) = 0;
        virtual void AddObject(const RenderSceneObject& object) = 0;
        virtual void AddLight(const RenderSceneLight& light) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------