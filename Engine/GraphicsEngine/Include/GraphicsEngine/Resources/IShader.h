// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct IShader
    {
        virtual const List<Uint8>& GetBytecode() const = 0;
        virtual EPipelineStage GetPipelineStage() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------