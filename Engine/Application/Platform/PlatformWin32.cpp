// Kasper "OstGeneralen" Esbjornsson - 2026
#if _WIN32
#include "Application.h"
#include "Platform.h"

#include <Windows.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

// ------------------------------------------------------------

void platform::Initialize()
{
    WNDCLASS windowClass = {};
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = "OstAppWndClass";
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = &WindowProc;
    RegisterClass(&windowClass);
}

// ------------------------------------------------------------

void platform::Shutdown()
{
    UnregisterClass("OstAppWndClass", GetModuleHandle(NULL));
}

// ------------------------------------------------------------

platform::NativeWindow platform::NewWindow(Application& hostApp, const std::string& title, const Vector2u& size, bool fullscreen)
{
    HWND window = CreateWindow("OstAppWndClass",             // Class name (as registered in initialize)
                               title.c_str(),                // Window title
                               WS_OVERLAPPEDWINDOW,          // Window style
                               CW_USEDEFAULT, CW_USEDEFAULT, // Window start position
                               size.X, size.Y,               // Window size
                               NULL,                         // Parent window
                               NULL,                         // Menu handle
                               GetModuleHandle(NULL),        // Instance handle
                               &hostApp                      // Creation data pointer
    );

    ShowWindow(window, SW_NORMAL);
    UpdateWindow(window);

    return window;
}

// ------------------------------------------------------------

void platform::WindowUpdate(NativeWindow nativeWindow)
{
    HWND window = static_cast<HWND>(nativeWindow);
    MSG msg = {};
    while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// ------------------------------------------------------------

void platform::CloseWindow(NativeWindow& nativeWindow)
{
    HWND window = static_cast<HWND>(nativeWindow);
    DestroyWindow(window);
    nativeWindow = nullptr;
}
// ------------------------------------------------------------

Vector2u platform::GetWindowSize(NativeWindow nativeWindow)
{
    HWND window = static_cast<HWND>(nativeWindow);
    RECT wndRect = {};
    Vector2u s = {};
    if (GetWindowRect(window, &wndRect))
    {
        s.X = wndRect.right - wndRect.left;
        s.Y = wndRect.bottom - wndRect.top;
    }
    return s;
}

// ------------------------------------------------------------

Vector2u platform::GetClientSize(NativeWindow nativeWindow)
{
    HWND window = static_cast<HWND>(nativeWindow);
    RECT wndRect = {};
    Vector2u s = {};
    if (GetClientRect(window, &wndRect))
    {
        s.X = wndRect.right - wndRect.left;
        s.Y = wndRect.bottom - wndRect.top;
    }
    return s;
}

// ------------------------------------------------------------

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Application* pApp = nullptr;

    if (msg == WM_CREATE)
    {
        const CREATESTRUCT* createData = reinterpret_cast<CREATESTRUCT*>(lparam);
        pApp = static_cast<Application*>(createData->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp));
    }
    else
    {
        pApp = reinterpret_cast<Application*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pApp == nullptr)
    {
        return DefWindowProc(hwnd, msg, wparam, lparam);
        // This is an error really :(
    }

    switch (msg)
    {
    case WM_CLOSE: {
        pApp->RequestExit();
        break;
    }
    case WM_ENTERSIZEMOVE: {

        pApp->BeginWindowResize();
        break;
    }
    case WM_EXITSIZEMOVE: {

        pApp->ExitWindowResize();
        break;
    }
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
#endif