// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsAssetsManager.h"

#include "Loaders/ModelLoader.h"

#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>

// ------------------------------------------------------------

void ost::GraphicsAssetsManager::SetResourceManager(IGraphicsResourceManager& gfxManager)
{
    _pGfxResourceManager = &gfxManager;
}

ost::ModelHandle ost::GraphicsAssetsManager::LoadModel(const std::string& path)
{
    ModelCPUData cpuData;
    ModelLoader loader;
    loader.Load(path, cpuData);

    return _pGfxResourceManager->Create(cpuData);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------