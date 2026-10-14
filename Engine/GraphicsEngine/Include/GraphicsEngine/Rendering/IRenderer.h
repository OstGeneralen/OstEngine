// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class IRenderQueue;
    struct RenderView;
    struct RendererContext;

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void Initialize(const Vector2u& size, RendererContext&& ctx) = 0;

        virtual void Resize(const Vector2u& newSize, RendererContext&& ctx) = 0;

        virtual Float32 GetAspectRatio() const = 0;
        virtual const Vector2f& GetDimensions() const = 0;

        virtual void ExecuteCommands( const IRenderQueue& renderQueue, RendererContext&& ctx) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------