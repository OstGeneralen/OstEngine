// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetGuid.h"

#include <OstTypes.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    enum class EAssetState
    {
        Pending,
        Loading,
        Loaded,
        Ready,
    };

    struct Asset
    {
        // Lookup data
        AssetGuid guid = {};
        std::string name = "";
        std::string path = "";

        // Load state
        EAssetState state = EAssetState::Pending;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------