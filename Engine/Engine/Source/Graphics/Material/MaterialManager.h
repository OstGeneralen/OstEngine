// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class MaterialManager
    {
    public:
        MaterialManager(IGraphicsResourceManager& gfxResourceManager);

                

    private:
        IGraphicsResourceManager& _graphicsResources;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------