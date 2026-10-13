// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/MaterialLoader.h"
#include "Loaders/ModelLoader.h"

using namespace ost;

// ------------------------------------------------------------

namespace ost
{
    SizeType LoadModel(const std::string& p, AssetContext&& ctx)
    {
        ModelCPUData loaded;
        ModelLoader loader;
        loader.Load(p, loaded);
        return static_cast<SizeType>(ctx.gfxResources.Create(loaded));
    }

    SizeType LoadImage(const std::string& p, AssetContext&& ctx)
    {
        TextureCPUData loaded;
        ImageLoader loader;
        loader.Load(p, loaded);
        return static_cast<SizeType>(ctx.gfxResources.Create(loaded));
    }

    SizeType LoadMaterial(const std::string& p, AssetContext&& ctx)
    {
        MaterialLoader loader;
        return static_cast<SizeType>(loader.LoadMaterial(p, ctx.assets, ctx.materials));
    }

    SizeType LoadMaterialInstance(const std::string& p, AssetContext&& ctx)
    {
        MaterialLoader loader;
        return static_cast<SizeType>(loader.LoadMaterialInstance(p, ctx.assets, ctx.materials));
    }

    SizeType CreateMaterial(AssetContext&& ctx, const void* pDesc)
    {
        return static_cast<SizeType>(ctx.materials.CreateMaterial(*static_cast<const MaterialDesc*>(pDesc)));
    }

    SizeType CreateMaterialInstance(AssetContext&& ctx, const void* pDesc)
    {
        return static_cast<SizeType>(ctx.materials.CreateInstance(*static_cast<const HMaterial*>(pDesc)));
    }

    void GetMaterial(AssetContext&& ctx, SizeType hnd, void** ppOut)
    {
        (*ppOut) = &ctx.materials.GetMaterial(HMaterial{hnd});
    }

    void CGetMaterial(ConstAssetContext&& ctx, SizeType hnd, const void** ppOut)
    {
        (*ppOut) = &ctx.materials.GetMaterial(HMaterial{hnd});
    }

    void GetMaterialInstance(AssetContext&& ctx, SizeType hnd, void** ppOut)
    {
        (*ppOut) = &ctx.materials.GetMaterialInstance(HMaterialInstance{hnd});
    }

    void CGetMaterialInstance(ConstAssetContext&& ctx, SizeType hnd, const void** ppOut)
    {
        (*ppOut) = &ctx.materials.GetMaterialInstance(HMaterialInstance{hnd});
    }
} // namespace ost

// ------------------------------------------------------------

void ost::AssetManager::Initialize(IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager, const AssetManagerConfig& config)
{
    _pGfxResourceManager = &gfxResourceManager;
    _pMaterialManager = &materialManager;

    _typeContainers.Insert(TypeID::Get<HModel>(), AssetTypeContainer(LoadModel, nullptr, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<HTexture>(), AssetTypeContainer(LoadImage, nullptr, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<IMaterial>(), AssetTypeContainer(LoadMaterial, CreateMaterial, GetMaterial, CGetMaterial));
    _typeContainers.Insert(TypeID::Get<IMaterialInstance>(), AssetTypeContainer(LoadMaterialInstance, CreateMaterialInstance, GetMaterialInstance, CGetMaterialInstance));

    _config = config;
    ScanAssets();
}

void ost::AssetManager::ScanAssets()
{
    _assetNameToPath.Clear();

    // Build Engine Assets tree
    auto assetTreeBuild = [this](const std::string& prefix, const std::string& root) {
        for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator{root})
        {
            if (directoryEntry.is_regular_file())
            {
                std::stringstream nameStream;
                nameStream << prefix << '/';
                nameStream << directoryEntry.path().stem().string();
                _assetNameToPath.Insert(nameStream.str(), std::filesystem::weakly_canonical(directoryEntry.path()).string());
            }
        }
    };

    assetTreeBuild(_config.engineAssetsPathConfig.prefix, _config.engineAssetsPathConfig.path);
    assetTreeBuild(_config.gameAssetsPathConfig.prefix, _config.gameAssetsPathConfig.path);
}

// ------------------------------------------------------------

void ost::AssetManager::GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, void** ppOut)
{
    _typeContainers[assetType].getFunc(MakeContext(), rawHnd, ppOut);
}

const void ost::AssetManager::GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, const void** ppOut) const
{
    _typeContainers[assetType].cGetFunc(MakeContext(), rawHnd, ppOut);
}

SizeType ost::AssetManager::CreateAsset(TypeID assetType, const std::string& name, const void* descData)
{
    auto& typeContainer = _typeContainers[assetType];

    const SizeType rawHandle = typeContainer.createFunc(MakeContext(), descData);
    typeContainer.nameToHandle.Insert(name, rawHandle);
    return rawHandle;
}

SizeType ost::AssetManager::LoadFromFile(TypeID assetType, const std::string& name)
{
    auto& typeContainer = _typeContainers[assetType];

    if (const SizeType* foundHandle = typeContainer.nameToHandle.TryGetValue(name))
    {
        // Already loaded so just return the handle :)
        return *foundHandle;
    }

    if (const std::string* path = _assetNameToPath.TryGetValue(name))
    {
        const SizeType rawHandle = _typeContainers[assetType].loadFunc(*path, MakeContext());

        typeContainer.nameToHandle.Insert(name, rawHandle);

        return rawHandle;
    }

    // Todo: Assert/Warn?
    return 0;
}

SizeType ost::AssetManager::GetHandleRaw(TypeID typeID, const std::string& name) const
{
    return _typeContainers[typeID].nameToHandle[name];
}

AssetContext ost::AssetManager::MakeContext()
{
    return AssetContext(*this, *_pGfxResourceManager, *_pMaterialManager);
}

ConstAssetContext ost::AssetManager::MakeContext() const
{
    return ConstAssetContext(*this, *_pGfxResourceManager, *_pMaterialManager);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------