// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetFactory.h"
#include "Engine/Asset/Model.h"

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class ModelFactory : public AssetFactoryBase
    {
    public:
        ModelFactory(IGraphicsResourceManager& gfxResourceManager);

        // BEGIN AssetFactoryBase
        TypeID AssetTypeID() const override;
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