// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderQueue.h"

// Resources
#include "Objects/Texture.h"
#include "Resources/GraphicsResourceManager.h"

// RHI
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"

// ------------------------------------------------------------

namespace ost
{
    struct RendererContext
    {
        RendererContext(const RenderHardwareInterface& r, GraphicsResourceManager& res, Texture bb)
            : rhi{r}
            , resources{res}
            , backbuffer{bb}
        {
        }

        const RenderHardwareInterface& rhi;
        GraphicsResourceManager& resources;

        Texture backbuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------