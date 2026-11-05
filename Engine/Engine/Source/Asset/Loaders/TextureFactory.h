// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetFactory.h"

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class TextureFactory : public AssetFactoryBase
    {
    public:
        TextureFactory(IGraphicsResourceManager& gfxResourceManager);

        // BEGIN AssetFactoryBase
        virtual TypeID AssetTypeID() const override;
        Asset* ConstructDefault() const override;
        void Load(const std::filesystem::path& path, Asset* pInto) const override;
        // END AssetFactoryBase

    private:
        IGraphicsResourceManager& _gfxResourceManager;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------