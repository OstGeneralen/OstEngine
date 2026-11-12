// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ITexture.h"

#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class IRenderQueue;
    struct RenderView;
    struct RendererContext;

    enum class ERenderOutputTexture
    {
        Output,
        Albedo,
        Normal,

    };

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void Initialize(const Vector2u& size, RendererContext&& ctx) = 0;

        virtual void ExecuteCommands(const IRenderQueue& renderQueue, RendererContext&& ctx) = 0;
        virtual const ITexture* GetOutputTarget(ERenderOutputTexture target = ERenderOutputTexture::Output) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------