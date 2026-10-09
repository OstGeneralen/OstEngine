// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"

#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetManager : public IAssetManager
    {
    public:
        void Initialize(IGraphicsResourceManager& gfxResourceManager);

    public: // IAssetManager
        TextureHandle LoadTextureFromFile(const std::filesystem::path& path) override;
        ModelHandle LoadModelFromFile(const std::filesystem::path& path) override;

        void Release(TextureHandle h) override;
        void Release(ModelHandle h) override;

    private:
        IGraphicsResourceManager* _pGfxResourceManager;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------