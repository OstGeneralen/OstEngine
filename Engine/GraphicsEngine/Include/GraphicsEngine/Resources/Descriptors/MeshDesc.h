// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    struct MeshDesc
    {
        SizeType vertexCount;
        SizeType vertexOffset = 0;
        SizeType indexCount;
        SizeType indexOffset = 0;
        SizeType materialIndex;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------