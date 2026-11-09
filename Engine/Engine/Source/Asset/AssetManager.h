// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"

#include <Container/Map.h>
#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetManager : public IAssetManager
    {
    public:
        AssetManager();

        // BEGIN IAssetManager
        void RegisterAssetFactory(UniquePtr<AssetFactoryBase>&& pFactory) override;
        // END IAssetManager

    protected:
        // BEGIN IAssetManager
        Asset* CreateDefault(TypeID type, std::string name) override;
        AssetFactoryBase* GetAssetFactory(TypeID type) override;
        Asset* GetOrLoad(TypeID type, const std::filesystem::path& path) override;
        // END IAssetManager

    private:
        Map<std::string, UniquePtr<Asset>> _assetRegistry;
        Map<TypeID, UniquePtr<AssetFactoryBase>> _factoryRegistry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------