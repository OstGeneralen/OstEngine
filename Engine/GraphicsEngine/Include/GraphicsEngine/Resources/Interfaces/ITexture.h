// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/Interfaces/IGraphicsResource.h"

#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HTexture);

    struct ITexture : public IGraphicsResource
    {
        virtual ETextureType GetTextureTypeFlags() const = 0;
        virtual EDataFormat GetTextureFormat(ETextureType texType) const = 0;
        virtual Vector2u GetResolution() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------