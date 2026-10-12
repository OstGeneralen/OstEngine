// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/ModelLoader.h"

using namespace ost;

// ------------------------------------------------------------

void ost::AssetManager::Initialize(IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager)
{
    _pGfxResourceManager = &gfxResourceManager;
    _pMaterialManager = &materialManager;
}

// ------------------------------------------------------------

HTexture AssetManager::LoadTextureFromFile(const std::filesystem::path& path)
{
    TextureCPUData loaded;
    ImageLoader loader;
    loader.Load(path.string(), loaded);
    return _pGfxResourceManager->Create(loaded);
}

HModel AssetManager::LoadModelFromFile(const std::filesystem::path& path)
{
    ModelCPUData loaded;
    ModelLoader loader;
    loader.Load(path.string(), loaded);
    return _pGfxResourceManager->Create(loaded);
}

// ------------------------------------------------------------

HMaterial ost::AssetManager::CreateMaterial(EMaterialDomain domain, const std::string& materialShader)
{
    return _pMaterialManager->CreateMaterial({domain, materialShader});
}

IMaterial& AssetManager::GetMaterial(HMaterial hnd)
{
    return _pMaterialManager->GetMaterial(hnd);
}

HMaterialInstance ost::AssetManager::CreateMaterialInstance(HMaterial fromMaterial)
{
    return _pMaterialManager->CreateInstance(fromMaterial);
}

IMaterialInstance& AssetManager::GetMaterialInstance(HMaterialInstance hnd)
{
    return _pMaterialManager->GetMaterialInstance(hnd);
}

// ------------------------------------------------------------

void AssetManager::Release(HTexture h)
{
    _pGfxResourceManager->Release(h);
}

void AssetManager::Release(HModel h)
{
    _pGfxResourceManager->Release(h);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------