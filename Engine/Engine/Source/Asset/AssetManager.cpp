// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include <OstLog.h>

#include <Memory/Memory.h>

using namespace ost;

// ------------------------------------------------------------

auto AssetManagerLog = Log::NewCategory("AssetManager");

// ------------------------------------------------------------

AssetManager::AssetManager()
{
}

// ------------------------------------------------------------

void ost::AssetManager::RegisterAssetFactory(UniquePtr<AssetFactoryBase>&& pFactory)
{
    _factoryRegistry.Insert(pFactory->AssetTypeID(), std::move(pFactory));
}

AssetFactoryBase* ost::AssetManager::GetAssetFactory(TypeID type)
{
    if (UniquePtr<AssetFactoryBase>* pFactory = _factoryRegistry.TryGetValue(type))
    {
        return pFactory->Get();
    }
    return nullptr;
}

// ------------------------------------------------------------

Asset* ost::AssetManager::CreateDefault(TypeID type, std::string name)
{
    if (UniquePtr<AssetFactoryBase>* ppFactory = _factoryRegistry.TryGetValue(type))
    {
        UniquePtr<Asset> pAsset(ppFactory->Get()->ConstructDefault());
        Asset* pReturn = pAsset.Get();
        _assetRegistry.Insert(name, std::move(pAsset));

        return pReturn;
    }

    Log::Error(AssetManagerLog, "Could not create default asset '{}', no type factory registered.", name);
    return nullptr;
}

// ------------------------------------------------------------

Asset* ost::AssetManager::GetOrLoad(TypeID type, const std::filesystem::path& path)
{
    // 1. Check the asset registry for if this path is already loaded
    if (UniquePtr<Asset>* pAsset = _assetRegistry.TryGetValue(path.string()))
    {
        if (pAsset->Get()->AssetTypeID() != type)
        {
            // ERROR!
            Log::Error(AssetManagerLog, "Asset Type Mismatch when getting '{}'", path.string());
            return nullptr;
        }

        return pAsset->Get();
    }
    // 2. If it wasn't already loaded, find the correct factory and load it
    else if (UniquePtr<AssetFactoryBase>* pFactory = _factoryRegistry.TryGetValue(type))
    {
        UniquePtr<Asset> pAsset(pFactory->Get()->ConstructDefault());
        pFactory->Get()->Load(path, pAsset.Get());

        Log::Log(AssetManagerLog, "Loaded asset '{}'", path.string());

        Asset* returnPtr = pAsset.Get();
        _assetRegistry.Insert(path.string(), std::move(pAsset));
        return returnPtr;
    }

    // If we get here, there's no valid factory registered so we have an error on our hands :(
    Log::Error(AssetManagerLog, "Could not load asset '{}', no type factory registered.", path.string());
    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------