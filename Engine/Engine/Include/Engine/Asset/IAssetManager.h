// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetType.h"

#include <filesystem>

#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class IAssetManager
    {
    public:
        template <typename TAsset>
        AssetTraits<TAsset>::HandleType GetHandle(const std::string& name)
        {
            return AssetTraits<TAsset>::HandleType(GetHandleRaw(TypeID::Get<TAsset>(), name));
        }

        template <typename TAsset>
        TAsset& GetAsset(AssetTraits<TAsset>::HandleType handle)
        {
            void* ptr = nullptr;
            GetAssetByRawHandle(TypeID::Get<TAsset>(), static_cast<SizeType>(handle), &ptr);
            return *static_cast<TAsset*>(ptr);
        }

        template <typename TAsset>
        const TAsset& GetAsset(AssetTraits<TAsset>::HandleType handle) const
        {
            const void* ptr = nullptr;
            GetConstAssetByRawHandle(TypeID::Get<TAsset>(), static_cast<SizeType>(handle), &ptr);
            return *static_cast<const TAsset*>(ptr);
        }

        template <typename TAsset>
        TAsset& Create(const std::string& name, const AssetTraits<TAsset>::DescType& desc)
        {
            const SizeType rawHandle = CreateAsset(TypeID::Get<TAsset>(), name, &desc);
            return GetAsset<TAsset>(AssetTraits<TAsset>::HandleType(rawHandle));
        }

        template <typename TAsset>
        AssetTraits<TAsset>::HandleType LoadFromFile(const std::string& name, const std::filesystem::path& path)
        {
            return AssetTraits<TAsset>::HandleType(LoadFromFile(TypeID::Get<TAsset>(), name, path));
        }

    protected:
        virtual void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, void** ppOut) = 0;
        virtual const void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, const void** ppOut) const = 0;
        virtual SizeType CreateAsset(TypeID assetType, const std::string& name, const void* descData) = 0;
        virtual SizeType LoadFromFile(TypeID assetType, const std::string& name, const std::filesystem::path& path) = 0;
        virtual SizeType GetHandleRaw(TypeID typeID, const std::string& name) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------