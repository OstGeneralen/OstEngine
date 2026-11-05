// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetFactory.h"
#include "Engine/Asset/AssetRef.h"

#include <filesystem>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IAssetManager
    {
    public: // Template Helpers
        template <typename TAsset>
        AssetRef<TAsset> GetOrLoad(const std::filesystem::path& path)
        {
            return AssetRef<TAsset>(static_cast<TAsset*>(GetOrLoad(TypeID::Get<TAsset>(), path)));
        }

        template <typename TFactory>
        TFactory* GetAssetFactory()
        {
            return static_cast<TFactory*>(GetAssetFactory(TypeID::Get<TFactory>()));
        }

    protected:
        virtual void RegisterAssetFactory(UniquePtr<AssetFactoryBase>&& pFactory) = 0;
        virtual AssetFactoryBase* GetAssetFactory(TypeID type) = 0;
        virtual Asset* GetOrLoad(TypeID type, const std::filesystem::path& path) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------