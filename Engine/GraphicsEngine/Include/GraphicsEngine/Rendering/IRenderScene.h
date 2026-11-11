// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Lights.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    struct RenderSceneCamera
    {
        Matrix4x4 viewProjection;
        Matrix4x4 viewInverse;
    };

    struct RenderSceneObject
    {
        HVertexBuffer vertexBuffer;
        HIndexBuffer indexBuffer;

        HShader vertexShader;
        HShader pixelShader;

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