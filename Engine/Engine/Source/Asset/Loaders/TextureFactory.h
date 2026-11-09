// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/AssetFactory.h"
#include "Engine/Graphics/Assets/TextureAsset.h"

#include <Math/Color.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class TextureFactory : public AssetFactoryBase
    {
    public:
        TextureFactory(IGraphicsResourceManager& gfxResourceManager);

        void CreateSingleColorTexture(const Vector2u& dimensions, const Color& color, TextureAsset& into);

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