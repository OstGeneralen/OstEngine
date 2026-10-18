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
        Output, // Primary output target
        Depth,  // Depth target

        GBufferAlbedo, // Albedo (Deferred only)
        GBufferNormal, // Normals (Deferred only)
        GBufferORM,    // ORM (Deferred only)
    };

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void Initialize(const Vector2u& size, RendererContext&& ctx) = 0;

        virtual void Resize(const Vector2u& newSize, RendererContext&& ctx) = 0;

        virtual Float32 GetAspectRatio() const = 0;
        virtual const Vector2f& GetDimensions() const = 0;

        virtual void ExecuteCommands(const IRenderQueue& renderQueue, RendererContext&& ctx) = 0;
        virtual const ITexture* GetOutputTarget(ERenderOutputTexture target = ERenderOutputTexture::Output) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------