// Kasper "OstGeneralen" Esbjornsson - 2026
#if WIN32
#include "Engine/Platform/Window.h"

#include <windows.h>

using namespace ost;

// ------------------------------------------------------------

LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

EKeyboard TranslateVirtualKey(WPARAM wp, LPARAM lp);

// ------------------------------------------------------------

void Window::Create(IWindowHost& host, const std::string& title, const Vector2u& size, bool fullscreen)
{
    _pHost = &host;

    WNDCLASS windowClass = {};
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = "OstAppWndClass";
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = &WindowProc;
    RegisterClass(&windowClass);

    UINT windowStyle = WS_OVERLAPPEDWINDOW;
    Vector2u useSize = size;

    if (fullscreen)
    {
        windowStyle = WS_POPUP;
        useSize.X = GetSystemMetrics(SM_CXSCREEN);
        useSize.Y = GetSystemMetrics(SM_CYSCREEN);
    }

    HWND hwnd = CreateWindow("OstAppWndClass",             // Class name (as registered in initialize)
                             title.c_str(),                // Window title
                             windowStyle,                  // Window style
                             CW_USEDEFAULT, CW_USEDEFAULT, // Window start position
                             useSize.X, useSize.Y,         // Window size
                             NULL,                         // Parent window
                             NULL,                         // Menu handle
                             GetModuleHandle(NULL),        // Instance handle
                             this                          // Creation data pointer
    );

    ShowWindow(hwnd, SW_NORMAL);
    UpdateWindow(hwnd);

    _nativeWindowHandle = hwnd;
}

void Window::Close()
{
    HWND hwnd = static_cast<HWND>(_nativeWindowHandle);
    DestroyWindow(hwnd);
    _nativeWindowHandle = nullptr;

    UnregisterClass("OstAppWndClass", GetModuleHandle(NULL));
}

void Window::Update()
{
    HWND hwnd = static_cast<HWND>(_nativeWindowHandle);

    MSG msg = {};
    while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// ------------------------------------------------------------

void Window::AddNativeWindowEventCallback(NativeWindowEventCallback callback)
{
    _nativeEventCallbacks.Add(callback);
}

// ------------------------------------------------------------

Vector2u Window::GetWindowSize() const
{
    HWND window = static_cast<HWND>(_nativeWindowHandle);
    RECT wndRect = {};
    Vector2u s = {};
    if (GetWindowRect(window, &wndRect))
    {
        s.X = wndRect.right - wndRect.left;
        s.Y = wndRect.bottom - wndRect.top;
    }
    return s;
}

Vector2u Window::GetClientSize() const
{
    HWND window = static_cast<HWND>(_nativeWindowHandle);
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

void* Window::GetNativeWindowHandle() const
{
    return _nativeWindowHandle;
}

// ------------------------------------------------------------

bool Window::InstanceWindowProcedure(const NativeWindowEventContext& ctx)
{
    for (auto& callback : _nativeEventCallbacks)
    {
        if (callback(ctx))
        {
            return true;
        }
    }

    switch (ctx.message)
    {
    case WM_CLOSE:
        _pHost->RequestExit();
        return true;
    case WM_EXITSIZEMOVE:
        _pHost->Resized();
        return true;
    case WM_SIZE: {
        if (ctx.wParam == SIZE_MAXIMIZED || ctx.wParam == SIZE_RESTORED)
        {
            _pHost->Resized();
            return true;
        }
        break;
    }
    case WM_KEYDOWN: {
        const EKeyboard key = TranslateVirtualKey(ctx.wParam, ctx.lParam);
        if (key != EKeyboard::Unknown)
        {
            _pHost->ProcessKeyEvent(key, true);
            return true;
        }
        break;
    }
    case WM_KEYUP: {
        const EKeyboard key = TranslateVirtualKey(ctx.wParam, ctx.lParam);
        if (key != EKeyboard::Unknown)
        {
            _pHost->ProcessKeyEvent(key, false);
            return true;
        }
        break;
    }
    }

    return false;
}

// ------------------------------------------------------------

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window* pWin = nullptr;

    if (msg == WM_CREATE)
    {
        const CREATESTRUCT* createData = reinterpret_cast<CREATESTRUCT*>(lparam);
        pWin = static_cast<Window*>(createData->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWin));
    }
    else
    {
        pWin = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pWin == nullptr)
    {
        return DefWindowProc(hwnd, msg, wparam, lparam);
        // This is an error really :(
    }

    NativeWindowEventContext context;
    context.nativeWindowHandle = hwnd;
    context.message = msg;
    context.lParam = lparam;
    context.wParam = wparam;
    if (pWin->InstanceWindowProcedure(context))
    {
        return 0;
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