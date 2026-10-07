// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Color.h>
#include <Math/Matrix4x4.h>
#include <Math/Vector4.h>

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

    struct alignas(16) LightsBuffer
    {
        struct alignas(16)
        {
            Vector4f direction = {0.0f, -1.0f, 0.0f, 0.0f};
            Color color = Colors::Black;
        } directional;

        struct alignas(16)
        {
            Color color = Colors::Black;
        } ambient;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------