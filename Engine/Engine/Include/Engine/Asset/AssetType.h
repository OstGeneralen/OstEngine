// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterial.h"
#include "GraphicsEngine/Materials/IMaterialInstance.h"
#include "GraphicsEngine/Resources/ITexture.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// ------------------------------------------------------------

#define DECLARE_ASSET_TYPE(AssetType, hndType, descType)                                                                                                                 \
    template <>                                                                                                                                                          \
    struct AssetTraits<AssetType>                                                                                                                                        \
    {                                                                                                                                                                    \
        using HandleType = hndType;                                                                                                                                      \
        using DescType = descType;                                                                                                                                       \
    };

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    struct AssetTraits
    {
        using HandleType = void;
        using DescType = void;
    };

    DECLARE_ASSET_TYPE(IMaterial, HMaterial, MaterialDesc);
    DECLARE_ASSET_TYPE(IMaterialInstance, HMaterialInstance, HMaterial);
    DECLARE_ASSET_TYPE(ITexture, HTexture, void);
    DECLARE_ASSET_TYPE(HModel, HModel, void);
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------