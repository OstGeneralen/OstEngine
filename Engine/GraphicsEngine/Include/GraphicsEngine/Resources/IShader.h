// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>

#include <Memory/BufferView.h>

// ------------------------------------------------------------

namespace ost
{
    struct IShader
    {
        virtual const BufferView& GetBytecode() const = 0;
        virtual EPipelineStage GetPipelineStage() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------