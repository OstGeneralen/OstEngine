// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"

#include <GraphicsEngine/Materials/IMaterialManager.h>
#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetManager : public IAssetManager
    {
    public:
        void Initialize(IGraphicsResourceManager& gfxResourceManager, IMaterialManager& materialManager);

        // BEGIN IAssetManager
        HTexture LoadTextureFromFile(const std::filesystem::path& path) override;
        HModel LoadModelFromFile(const std::filesystem::path& path) override;

        HMaterial CreateMaterial(EMaterialDomain domain, const std::string& materialShader) override;
        IMaterial& GetMaterial(HMaterial hnd) override;

        HMaterialInstance CreateMaterialInstance(HMaterial fromMaterial) override;
        IMaterialInstance& GetMaterialInstance(HMaterialInstance hnd) override;

        void Release(HTexture h) override;
        void Release(HModel h) override;
        // END IAssetManager

    private:
        IGraphicsResourceManager* _pGfxResourceManager;
        IMaterialManager* _pMaterialManager;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------