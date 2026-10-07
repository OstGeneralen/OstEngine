// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <GraphicsEngine/Objects/Model.h>
#include <GraphicsEngine/Objects/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    struct ModelAsset : Asset
    {
        ModelHandle gpuHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------