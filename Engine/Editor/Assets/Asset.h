// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <filesystem>

#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EAssetType
    {
        Config,    // .json
        Material,  // .ostmat (but it is json really)
        Model,     // fbx
        Texture2D, // dds
    };

    struct Asset
    {
        EAssetType type;
        std::filesystem::path importPath;
        union {
            HModel hModel;
            HTexture hTexture;
            HMaterialInstance hMaterial;
        } handle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------