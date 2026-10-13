// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>

// ------------------------------------------------------------

namespace ost
{
    class IAssetManager;
    class IMaterialManager;

    class MaterialLoader
    {
    public:
        HMaterial LoadMaterial(const std::string& path, IAssetManager& assets, IMaterialManager& materials);
        HMaterialInstance LoadMaterialInstance(const std::string& path, IAssetManager& assets, IMaterialManager& materials);
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------