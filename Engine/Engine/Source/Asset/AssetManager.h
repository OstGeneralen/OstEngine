// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"

#include <Container/Map.h>

#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;
    class IMaterialManager;

    struct AssetContext
    {
        AssetContext(IAssetManager& am, IGraphicsResourceManager& grm, IMaterialManager& mm)
            : assets{am}
            , gfxResources{grm}
            , materials{mm}
        {
        }

        IAssetManager& assets;
        IGraphicsResourceManager& gfxResources;
        IMaterialManager& materials;
    };

    struct ConstAssetContext
    {
        ConstAssetContext(const IAssetManager& am, const IGraphicsResourceManager& grm, const IMaterialManager& mm)
            : assets{am}
            , gfxResources{grm}
            , materials{mm}
        {
        }

        const IAssetManager& assets;
        const IGraphicsResourceManager& gfxResources;
        const IMaterialManager& materials;
    };

    struct AssetTypeContainer
    {
        typedef SizeType (*LoadFunc)(const std::string&, AssetContext&&);
        typedef SizeType (*CreateFunc)(AssetContext&&, const void*);
        typedef void (*GetFunc)(AssetContext&&, SizeType, void**);
        typedef void (*CGetFunc)(ConstAssetContext&&, SizeType, const void**);

        AssetTypeContainer() = default;
        AssetTypeContainer(AssetTypeContainer&&) noexcept = default;
        AssetTypeContainer(const AssetTypeContainer&) = delete;

        AssetTypeContainer(LoadFunc l, CreateFunc c, GetFunc g, CGetFunc cg)
            : loadFunc{l}
            , createFunc{c}
            , getFunc{g}
            , cGetFunc{cg}
        {
        }

        LoadFunc loadFunc = nullptr;
        CreateFunc createFunc = nullptr;
        GetFunc getFunc = nullptr;
        CGetFunc cGetFunc = nullptr;

        Map<std::string, SizeType> nameToHandle;
    };

    class AssetManager : public IAssetManager
    {
    public:
        AssetManager(ServiceLocator& serviceLocator);

    protected:
        // BEGIN IAssetManager
        void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, void** ppOut) override;
        const void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, const void** ppOut) const override;

        SizeType CreateAsset(TypeID assetType, const std::string& name, const void* descData) override;
        SizeType LoadFromFile(TypeID assetType, const std::string& path) override;
        SizeType GetHandleRaw(TypeID typeID, const std::string& name) const override;
        // END IAssetManager

    private:
        AssetContext MakeContext();
        ConstAssetContext MakeContext() const;

        ServiceLocator& _serviceLocator;

        Map<TypeID, AssetTypeContainer> _typeContainers;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------