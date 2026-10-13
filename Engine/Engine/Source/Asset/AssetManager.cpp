// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/ModelLoader.h"

using namespace ost;

// ------------------------------------------------------------

namespace ost
{
    SizeType LoadModel(const std::string& p, IGraphicsResourceManager& rm, IMaterialManager& mm)
    {
        ModelCPUData loaded;
        ModelLoader loader;
        loader.Load(p, loaded);
        return static_cast<SizeType>(rm.Create(loaded));
    }

    SizeType LoadImage(const std::string& p, IGraphicsResourceManager& rm, IMaterialManager& mm)
    {
        TextureCPUData loaded;
        ImageLoader loader;
        loader.Load(p, loaded);
        return static_cast<SizeType>(rm.Create(loaded));
    }

    SizeType CreateMaterial(IGraphicsResourceManager& rm, IMaterialManager& mm, const void* pDesc)
    {
        return static_cast<SizeType>(mm.CreateMaterial(*static_cast<const MaterialDesc*>(pDesc)));
    }

    SizeType CreateMaterialInstance(IGraphicsResourceManager& rm, IMaterialManager& mm, const void* pDesc)
    {
        return static_cast<SizeType>(mm.CreateInstance(*static_cast<const HMaterial*>(pDesc)));
    }

    void GetMaterial(IGraphicsResourceManager& rm, IMaterialManager& mm, SizeType hnd, void** ppOut)
    {
        (*ppOut) = &mm.GetMaterial(HMaterial{hnd});
    }

    void CGetMaterial(IGraphicsResourceManager& rm, IMaterialManager& mm, SizeType hnd, const void** ppOut)
    {
        (*ppOut) = &mm.GetMaterial(HMaterial{hnd});
    }

    void GetMaterialInstance(IGraphicsResourceManager& rm, IMaterialManager& mm, SizeType hnd, void** ppOut)
    {
        (*ppOut) = &mm.GetMaterialInstance(HMaterialInstance{hnd});
    }

    void CGetMaterialInstance(IGraphicsResourceManager& rm, IMaterialManager& mm, SizeType hnd, const void** ppOut)
    {
        (*ppOut) = &mm.GetMaterialInstance(HMaterialInstance{hnd});
    }
} // namespace ost

// ------------------------------------------------------------

void ost::AssetManager::Initialize(IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager)
{
    _pGfxResourceManager = &gfxResourceManager;
    _pMaterialManager = &materialManager;

    _typeContainers.Insert(TypeID::Get<HModel>(), AssetTypeContainer(LoadModel, nullptr, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<HTexture>(), AssetTypeContainer(LoadImage, nullptr, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<IMaterial>(), AssetTypeContainer(nullptr, CreateMaterial, GetMaterial, CGetMaterial));
    _typeContainers.Insert(TypeID::Get<IMaterialInstance>(), AssetTypeContainer(nullptr, CreateMaterialInstance, GetMaterialInstance, CGetMaterialInstance));
}

// ------------------------------------------------------------

void ost::AssetManager::GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, void** ppOut)
{
    _typeContainers[assetType].getFunc(*_pGfxResourceManager, *_pMaterialManager, rawHnd, ppOut);
}

const void ost::AssetManager::GetAssetByRawHandle(TypeID assetType, SizeType rawHnd, const void** ppOut) const
{
    _typeContainers[assetType].cGetFunc(*_pGfxResourceManager, *_pMaterialManager, rawHnd, ppOut);
}

SizeType ost::AssetManager::CreateAsset(TypeID assetType, const std::string& name, const void* descData)
{
    auto& typeContainer = _typeContainers[assetType];

    const SizeType rawHandle = typeContainer.createFunc(*_pGfxResourceManager, *_pMaterialManager, descData);
    typeContainer.nameToHandle.Insert(name, rawHandle);
    return rawHandle;
}

SizeType ost::AssetManager::LoadFromFile(TypeID assetType, const std::string& name, const std::filesystem::path& path)
{
    // Normalize Path
    const std::string normalizedPath = std::filesystem::weakly_canonical(path).string();

    auto& typeContainer = _typeContainers[assetType];

    if (const std::string* foundName = typeContainer.pathToName.TryGetValue(normalizedPath))
    {
        // Todo: Probably warn here?
        return typeContainer.nameToHandle[*foundName];
    }

    const SizeType rawHandle = _typeContainers[assetType].loadFunc(normalizedPath, *_pGfxResourceManager, *_pMaterialManager);

    typeContainer.pathToName.Insert(normalizedPath, name);
    typeContainer.nameToHandle.Insert(name, rawHandle);

    return rawHandle;
}

SizeType ost::AssetManager::GetHandleRaw(TypeID typeID, const std::string& name) const
{
    return _typeContainers[typeID].nameToHandle[name];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------