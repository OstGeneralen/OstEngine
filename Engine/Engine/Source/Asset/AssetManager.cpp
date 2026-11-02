// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/MaterialLoader.h"
#include "Loaders/ModelLoader.h"

#include <GraphicsEngine/Materials/IMaterialManager.h>
#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>
#include <Memory/Memory.h>

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

    SizeType CreateImage(AssetContext&& ctx, const void* pDesc)
    {
        return static_cast<SizeType>(ctx.gfxResources.Create(*static_cast<const TextureCPUData*>(pDesc)));
    };

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

ost::AssetManager::AssetManager(ServiceLocator& serviceLocator)
    : _serviceLocator{serviceLocator}
    , _typeContainers{}
{
    _typeContainers.Insert(TypeID::Get<HModel>(), AssetTypeContainer(LoadModel, nullptr, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<ITexture>(), AssetTypeContainer(LoadImage, CreateImage, nullptr, nullptr));
    _typeContainers.Insert(TypeID::Get<IMaterial>(), AssetTypeContainer(LoadMaterial, CreateMaterial, GetMaterial, CGetMaterial));
    _typeContainers.Insert(TypeID::Get<IMaterialInstance>(), AssetTypeContainer(LoadMaterialInstance, CreateMaterialInstance, GetMaterialInstance, CGetMaterialInstance));

    // Generate Default Assets
    TextureCPUData defaultDataAlbedo = GenerateDefaultAssetData_AlbedoTexture();
    CreateAsset(TypeID::Get<ITexture>(), std::string(DefaultAssetName_AlbedoTexture), &defaultDataAlbedo);

    TextureCPUData defaultDataNormal = GenerateDefaultAssetData_NormalTexture();
    CreateAsset(TypeID::Get<ITexture>(), std::string(DefaultAssetName_NormalTexture), &defaultDataNormal);

    TextureCPUData defaultDataORM = GenerateDefaultAssetData_ORMTexture();
    CreateAsset(TypeID::Get<ITexture>(), std::string(DefaultAssetName_ORMTexture), &defaultDataORM);

    IAssetManager* thisInterface = this;
    HMaterial defaultLit = thisInterface->Load<IMaterial>("Engine/Materials/Mat_DefaultLit.json");
    auto& defaultLitInstance = Create<IMaterialInstance>(std::string(DefaultAssetName_LitMaterial), defaultLit);
    defaultLitInstance.Textures().SetTexture(0, thisInterface->GetHandle<ITexture>(std::string(DefaultAssetName_AlbedoTexture)));
    defaultLitInstance.Textures().SetTexture(1, thisInterface->GetHandle<ITexture>(std::string(DefaultAssetName_NormalTexture)));
    defaultLitInstance.Textures().SetTexture(2, thisInterface->GetHandle<ITexture>(std::string(DefaultAssetName_ORMTexture)));

    DefaultAssetHandle_LitMaterial = thisInterface->GetHandle<IMaterialInstance>(std::string(DefaultAssetName_LitMaterial));
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

SizeType ost::AssetManager::LoadFromFile(TypeID assetType, const std::string& path)
{
    auto& typeContainer = _typeContainers[assetType];

    if (const SizeType* foundHandle = typeContainer.nameToHandle.TryGetValue(path))
    {
        // Already loaded so just return the handle :)
        return *foundHandle;
    }

    const SizeType rawHandle = _typeContainers[assetType].loadFunc(path, MakeContext());
    typeContainer.nameToHandle.Insert(path, rawHandle);
    return rawHandle;
}

SizeType ost::AssetManager::GetHandleRaw(TypeID typeID, const std::string& name) const
{
    return _typeContainers[typeID].nameToHandle[name];
}

AssetContext ost::AssetManager::MakeContext()
{
    return AssetContext(*this, _serviceLocator.GetRequired<IGraphicsResourceManager>(), _serviceLocator.GetRequired<IMaterialManager>());
}

ConstAssetContext ost::AssetManager::MakeContext() const
{
    return ConstAssetContext(*this, _serviceLocator.GetRequired<IGraphicsResourceManager>(), _serviceLocator.GetRequired<IMaterialManager>());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------