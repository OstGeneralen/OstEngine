// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetManager.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/ModelLoader.h"

using namespace ost;

// ------------------------------------------------------------

void ost::AssetManager::Initialize(IGraphicsResourceManager& gfxResourceManager)
{
    _pGfxResourceManager = &gfxResourceManager;
}

// ------------------------------------------------------------

TextureHandle AssetManager::LoadTextureFromFile(const std::filesystem::path& path)
{
    TextureCPUData loaded;
    ImageLoader loader;
    loader.Load(path.string(), loaded);
    return _pGfxResourceManager->Create(loaded);
}

ModelHandle AssetManager::LoadModelFromFile(const std::filesystem::path& path)
{
    ModelCPUData loaded;
    ModelLoader loader;
    loader.Load(path.string(), loaded);
    return _pGfxResourceManager->Create(loaded);
}

// ------------------------------------------------------------

void AssetManager::Release(TextureHandle h)
{
    _pGfxResourceManager->Release(h);
}

void AssetManager::Release(ModelHandle h)
{
    _pGfxResourceManager->Release(h);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------