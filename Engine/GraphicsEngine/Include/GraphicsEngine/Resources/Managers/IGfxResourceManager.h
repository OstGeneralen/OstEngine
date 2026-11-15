// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Managers/IGfxBufferManager.h"
#include "GraphicsEngine/Resources/Managers/IGfxShaderManager.h"
#include "GraphicsEngine/Resources/Managers/IGfxTextureManager.h"

// ------------------------------------------------------------

namespace ost
{
    class IGfxResourceManager
    {
    public:
        IGfxResourceManager(IGfxBufferManager& b, IGfxTextureManager& t, IGfxShaderManager& s)
            : buffers{b}
            , textures{t}
            , shaders{s}
        {
        }

        IGfxBufferManager& buffers;
        IGfxTextureManager& textures;
        IGfxShaderManager& shaders;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------