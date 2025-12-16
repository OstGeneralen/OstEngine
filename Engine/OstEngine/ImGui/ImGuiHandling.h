#pragma once
#include <OstEngine/OstEngineMinimal.h>

namespace ost
{
    class CWindow;
    class CDXRenderer;

    namespace DeveloperGUI
    {
        extern void Init(CWindow& aWindow);
        extern void Deinit();

        extern void BeginFrame();
        extern void EndFrame();

        extern bool WndProcHandling(CWindow& aWindow, Uint32 aMsg, Int64 wparam, Uint64 lparam);
    }
} // namespace ost