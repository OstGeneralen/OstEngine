// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Resources/Descriptors/TextureDesc.h>
#include <string>
#include "Engine/Asset/AssetFactory.h"

// ------------------------------------------------------------

namespace ost
{
    class ImageLoader : public AssetFactoryBase
    {
    public:
        void Load(const std::string& path, TextureCPUData& into) const; 
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------