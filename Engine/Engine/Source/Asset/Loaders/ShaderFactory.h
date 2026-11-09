// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetFactory.h"

// ------------------------------------------------------------

namespace ost
{
    class ShaderFactory : public AssetFactoryBase
    {
    public:
        // BEGIN AssetFactoryBase
        TypeID AssetTypeID() const override;
        Asset* ConstructDefault() const override;
        void Load(const std::filesystem::path& path, Asset* pInto) const override;
        // END AssetFactoryBase
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------