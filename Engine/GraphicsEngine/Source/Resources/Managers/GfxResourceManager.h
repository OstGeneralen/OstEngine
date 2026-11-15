// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Managers/IGfxResourceManager.h"
#include "Resources/Managers/GfxBufferManager.h"
#include "Resources/Managers/GfxShaderManager.h"
#include "Resources/Managers/GfxTextureManager.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GfxResourceManager : public IGfxResourceManager
    {
    public:
        GfxResourceManager(const RenderHardwareInterface& rhi)
            : IGfxResourceManager(bufferManager, textureManager, shaderManager)
            , bufferManager{rhi}
            , textureManager{rhi}
            , shaderManager{rhi}
        {
        }

        GfxBufferManager bufferManager;
        GfxTextureManager textureManager;
        GfxShaderManager shaderManager;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------