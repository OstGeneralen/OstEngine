// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <functional>
#include <string>

#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class Application;
}

namespace ost::platform
{
    typedef void* NativeWindow;

    extern void Initialize();
    extern void Shutdown();
    extern NativeWindow NewWindow(Application& hostApp, const std::string& title, const Vector2u& size, bool fullscreen = false);
    extern void WindowUpdate(NativeWindow window);
    extern void CloseWindow(NativeWindow& window);
    extern Vector2u GetWindowSize(NativeWindow window);
    extern Vector2u GetClientSize(NativeWindow window);
} // namespace ost::platform

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------