// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

namespace ost
{
    using HTexture = TypedIntegerHandle<struct HNDType_Texture>;
    using HPipelineState = TypedIntegerHandle<struct HNDType_PSO>;
    using HModel = TypedIntegerHandle<struct HNDType_Model>;
    using HMesh = TypedIntegerHandle<struct HNDType_Mesh>;
    using HBuffer = TypedIntegerHandle<struct HNDType_Buffer>;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------