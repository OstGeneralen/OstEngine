// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
    struct MaterialAsset : public Asset
    {
        // BEGIN Asset
        TypeID AssetTypeID() const override
        {
            return TypeID::Get<MaterialAsset>();
        }
        // END Asset

    private:
        std::filesystem::path _materialShaderPath;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------