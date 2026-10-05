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
        StaticModelDesc cpuData;
        ModelHandle gpuHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------