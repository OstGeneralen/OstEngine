// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

// ------------------------------------------------------------

namespace ost
{
    struct IShader;

    struct IPipelineStateObject
    {
        virtual const IShader* GetShader(EPipelineStage stage) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------