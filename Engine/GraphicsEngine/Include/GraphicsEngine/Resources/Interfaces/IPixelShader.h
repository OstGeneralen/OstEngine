// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/Interfaces/IGraphicsResource.h"

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HPixelShader);

    struct IPixelShader : public IGraphicsResource
    {
        virtual EBlendMode GetBlendMode() const = 0;
        virtual SizeType GetTargetCount() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------