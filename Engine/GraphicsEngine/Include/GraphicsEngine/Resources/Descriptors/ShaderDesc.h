// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <string>

#include <Memory/BufferView.h>

// ------------------------------------------------------------

namespace ost
{
    struct ShaderDesc
    {
        EPipelineStage pipelineStage;
        BufferView bytecodeView;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------