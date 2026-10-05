// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <GraphicsEngine/Objects/ObjectHandles.h>
#include <GraphicsEngine/Objects/Texture.h>

// ------------------------------------------------------------

namespace ost
{
    struct ImageAsset : Asset
    {
        ResourceTextureDesc cpuData;
        TextureHandle gpuHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------