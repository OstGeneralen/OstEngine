// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/RHI/RHIMinimal.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    extern List<Uint8> CompileShaderFromFile(const std::string& filePath, EPipelineStage targetStage );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------