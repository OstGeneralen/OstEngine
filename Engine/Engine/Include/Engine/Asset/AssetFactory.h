// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <filesystem>

#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Asset;

    class AssetFactoryBase
    {
    public:
        virtual ~AssetFactoryBase() = default;
        virtual TypeID AssetTypeID() const = 0;

        virtual Asset* ConstructDefault() const = 0;
        virtual void Load(const std::filesystem::path& path, Asset* pInto) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------