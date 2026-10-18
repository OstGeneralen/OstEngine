// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderQueue.h"

// Resources
#include "Objects/Texture.h"
#include "Objects/Buffer.h"
#include "Resources/GraphicsResourceManager.h"

// RHI
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"

// ------------------------------------------------------------

namespace ost
{
    struct RendererContext
    {
        RendererContext(const RenderHardwareInterface& r, GraphicsResourceManager& res, Buffer fb, Buffer ob, Buffer lb)
            : rhi{r}
            , resources{res}
            , frameBuffer{fb}
            , lightBuffer{lb}
            , objectBuffer{ob}
        {
        }

        const RenderHardwareInterface& rhi;
        GraphicsResourceManager& resources;

        Buffer frameBuffer;
        Buffer lightBuffer;
        Buffer objectBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------