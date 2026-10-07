// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Rendering/Light.h"

#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void PushRenderCommand(const ModelHandle& model, const Matrix4x4& transform) = 0;
        virtual void PushLightCommand(const RenderLight& light) = 0;

        virtual void ExecuteRenderCommands(const Matrix4x4& view) = 0;
        virtual void ClearRenderCommands() = 0;


        virtual Vector2f GetRenderDimensions() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------