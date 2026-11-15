// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IGraphicsResource.h"

#include <string>

#include <Container/List.h>
#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HShaderStub);

    struct ShaderStub
    {
        List<std::string> defines;
        Map<std::string, std::string> includeRemaps;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------