// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <string>

#include <GraphicsEngine/Objects/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class GraphicsAssetsManager
    {
    public:
        void SetResourceManager(IGraphicsResourceManager& gfxManager);

        ModelHandle LoadModel(const std::string& modelFilePath);

    private:
        IGraphicsResourceManager* _pGfxResourceManager;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------