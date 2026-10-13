// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"

#include <Container/Map.h>
#include <GraphicsEngine/Materials/IMaterialManager.h>
#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>

// ------------------------------------------------------------

namespace ost
{
    struct AssetTypeContainer
    {
        typedef SizeType (*LoadFunc)(const std::string&, IGraphicsResourceManager&, IMaterialManager&);
        typedef SizeType (*CreateFunc)(IGraphicsResourceManager&, IMaterialManager&, const void*);
        typedef void (*GetFunc)(IGraphicsResourceManager&, IMaterialManager&, SizeType, void**);
        typedef void (*CGetFunc)(IGraphicsResourceManager&, IMaterialManager&, SizeType, const void**);

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
        Map<std::string, std::string> pathToName;
    };

    class AssetManager : public IAssetManager
    {
    public:
        void Initialize(IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager);

    protected:
        // BEGIN IAssetManager
        void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, void** ppOut) override;
        const void GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, const void** ppOut) const override;

        SizeType CreateAsset(TypeID assetType, const std::string& name, const void* descData) override;
        SizeType LoadFromFile(TypeID assetType, const std::string& name, const std::filesystem::path& path) override;
        SizeType GetHandleRaw(TypeID typeID, const std::string& name) const override;
        // END IAssetManager

    private:
        IGraphicsResourceManager* _pGfxResourceManager;
        IMaterialManager* _pMaterialManager;

        Map<TypeID, AssetTypeContainer> _typeContainers;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------