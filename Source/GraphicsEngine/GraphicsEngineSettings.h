// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Color.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct GraphicsEngineSettings
    {
        struct OutputSettings
        {
            void* nativeWindowHandle = nullptr; // The handle of the window (for Win32 this is your HWND)
            Vector2u clientSize = {1600, 900};  // The resolution in pixels of the target
            Vector2f renderSize = {1, 1};       // The percentage of the client resolution to render at
        } output;

        struct RenderSettings
        {
            Color clearColor = Colors::Black;
        } renderer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------