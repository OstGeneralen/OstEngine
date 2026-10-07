// Kasper "OstGeneralen" Esbjornsson - 2026
#if _WIN32
#include "Application.h"
#include "Platform.h"

#include <Windows.h>

#include <Engine/System/InputReader.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

EKeyboard TranslateVirtualKey(WPARAM wp, LPARAM lp);

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
        return 0;
        break;
    }
    case WM_ENTERSIZEMOVE: {

        pApp->BeginWindowResize();
        return 0;
        break;
    }
    case WM_EXITSIZEMOVE: {

        pApp->ExitWindowResize();
        return 0;
        break;
    }
    case WM_SIZE: {
        if (wparam == SIZE_MAXIMIZED || wparam == SIZE_RESTORED)
        {
            pApp->ExitWindowResize();
            return 0;
        }
        break;
    }
    case WM_KEYDOWN: {
        const EKeyboard key = TranslateVirtualKey(wparam, lparam);
        if (key != EKeyboard::Unknown)
        {
            pApp->ProcessKeyEvent(key, true);
        }
        break;
    }
    case WM_KEYUP: {
        const EKeyboard key = TranslateVirtualKey(wparam, lparam);
        if (key != EKeyboard::Unknown)
        {
            pApp->ProcessKeyEvent(key, false);
        }
        break;
    }
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

// ------------------------------------------------------------

EKeyboard TranslateVirtualKey(WPARAM wp, LPARAM lp)
{
    if (wp >= 'A' && wp <= 'Z')
    {
        return static_cast<EKeyboard>(static_cast<SizeType>(EKeyboard::A) + (wp - 'A'));
    }
    if (wp >= VK_NUMPAD0 && wp <= VK_NUMPAD9)
    {
        return static_cast<EKeyboard>(static_cast<SizeType>(EKeyboard::NumPad0) + (wp - VK_NUMPAD0));
    }
    if (wp >= '0' && wp <= '9')
    {
        return static_cast<EKeyboard>(static_cast<SizeType>(EKeyboard::Num0) + (wp - '0'));
    }

    WORD vkCode = LOWORD(wp);
    WORD flags = HIWORD(lp);

    WORD scanCode = LOBYTE(flags);
    BOOL isExtended = (flags & KF_EXTENDED) == KF_EXTENDED;

    if (isExtended)
    {
        scanCode = MAKEWORD(scanCode, 0xE0);
    }

    // This is to convert from just VK_SHIFT into VK_LSHIFT and RSHIFT
    // I don't like the ergonomics of this at all :)
    switch (vkCode)
    {
    case VK_SHIFT:
    case VK_CONTROL:
        vkCode = LOWORD(MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX));
        break;
    }

    switch (vkCode)
    {
    case VK_LSHIFT:
        return EKeyboard::LShift;
    case VK_RSHIFT:
        return EKeyboard::RShift;
    case VK_LCONTROL:
        return EKeyboard::LCtrl;
    case VK_RCONTROL:
        return EKeyboard::RCtrl;
    case VK_RETURN:
        return EKeyboard::Return;
    case VK_SPACE:
        return EKeyboard::Space;
    case VK_UP:
        return EKeyboard::Up;
    case VK_DOWN:
        return EKeyboard::Down;
    case VK_LEFT:
        return EKeyboard::Left;
    case VK_RIGHT:
        return EKeyboard::Right;
    }

    return EKeyboard::Unknown;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
#endif