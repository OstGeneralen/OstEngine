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

    protected:
        // BEGIN IAssetManager
        void RegisterAssetFactory(UniquePtr<AssetFactoryBase>&& pFactory) override;
        AssetFactoryBase* GetAssetFactory(TypeID type) override;
        Asset* GetOrLoad(TypeID type, const std::filesystem::path& path) override;
        // END IAssetManager

    private:
        Map<std::filesystem::path, UniquePtr<Asset>> _assetRegistry;
        Map<TypeID, UniquePtr<AssetFactoryBase>> _factoryRegistry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------