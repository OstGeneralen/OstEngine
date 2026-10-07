// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector4.h>
#include <Math/Matrix4x4.h>
#include <Math/Color.h>

// ------------------------------------------------------------

namespace ost
{
    struct alignas(16) FrameBufferStructure
    {
        Matrix4x4 viewMatrix;
        Matrix4x4 inverseViewMatrix;
    };

    struct alignas(16) ObjectBufferStructure
    {
        Matrix4x4 objectTransform;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------