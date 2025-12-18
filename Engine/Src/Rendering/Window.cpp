#include "OstEngine/Rendering/Window.h"

#include <OstEngine/Debug/Logging/Logger.h>

#include <Windows.h>
#include <iostream>

// ------------------------------------------------------------

LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
    case WM_CREATE: {
        LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>( lParam );
        ost::CWindow* winPtr = reinterpret_cast<ost::CWindow*>( createStruct->lpCreateParams );
        SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( winPtr ) );
        return 0;
    }
    }

    ost::CWindow* windowPtr = reinterpret_cast<ost::CWindow*>( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
    if ( windowPtr != NULL )
    {
        if ( windowPtr->EventCallbackFunction()( message, wParam, lParam ) )
        {
            return 0;
        }
    }

    return DefWindowProc( hWnd, message, wParam, lParam );
}

// ------------------------------------------------------------

ost::CWindow::CWindow()
    : _winPtr{}
    , _isOpen{ false }
{
}

// ------------------------------------------------------------

ost::CWindow::CWindow( const char* aTitle, const Vector2i& aSize, void* aAppInstance, bool aIncludeConsole )
{
    const std::string titleStr = aTitle;
    const std::wstring titleWstr{ titleStr.begin(), titleStr.end() };
    _size = aSize;

    HINSTANCE appInstance = static_cast<HINSTANCE>( aAppInstance );

    // Window Class
    WNDCLASSEX winClass;
    ZeroMemory( &winClass, sizeof( winClass ) );
    winClass.cbSize = sizeof( winClass );
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc = WindowProcedure;
    winClass.hInstance = appInstance;
    winClass.hCursor = LoadCursor( NULL, IDC_ARROW );
    winClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    winClass.lpszClassName = L"OstEngineWindowClass";

    RegisterClassEx( &winClass );

    _size = aSize;
    // clang-format off
    _winPtr = CreateWindowEx(
        0,
        L"OstEngineWindowClass",
        L"TEST",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        aSize.X, aSize.Y,
        NULL,
        NULL,
        appInstance,
        this
    );
    // clang-format on

    _isOpen = _winPtr;

    if ( aIncludeConsole && AllocConsole() )
    {
        FILE* stdOut = nullptr;
        if ( freopen_s( &stdOut, "CONOUT$", "w", stdout ) != 0 )
        {
        }

        FILE* stdIn = nullptr;
        if ( freopen_s( &stdIn, "CONOUT$", "r", stdin ) != 0 )
        {
        }

        std::cout.clear();
        std::cin.clear();
        std::cerr.clear();

        log::CLogger::Instance().EnableConsoleLogging();
    }
}

// ------------------------------------------------------------

ost::CWindow::~CWindow()
{
    if ( _winPtr )
    {
        DestroyWindow( _winPtr.Get<HWND>() );
        void* n = nullptr;
        _winPtr = n;
    }
}

// ------------------------------------------------------------

ost::CWindow::CWindow( CWindow&& aOther ) noexcept
    : _winPtr{ aOther._winPtr }
    , _isOpen{ aOther._isOpen }
    , _size{ aOther._size }
{
    void* n = nullptr;
    aOther._winPtr = n;
    SetWindowLongPtr( _winPtr.Get<HWND>(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>( this ) );
}

// ------------------------------------------------------------

ost::CWindow& ost::CWindow::operator=( CWindow&& aRhs ) noexcept
{
    _winPtr = aRhs._winPtr;
    void* n = nullptr;
    aRhs._winPtr = n;
    _isOpen = aRhs._isOpen;
    _size = aRhs._size;

    // Update the window pointer
    SetWindowLongPtr( _winPtr.Get<HWND>(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>( this ) );
    return *this;
}

// ------------------------------------------------------------

void ost::CWindow::RunEventLoop()
{
    ShowWindow( _winPtr.Get<HWND>(), 1 );
    UpdateWindow( _winPtr.Get<HWND>() );

    MSG msg = {};
    while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
}

// ------------------------------------------------------------

void ost::CWindow::BindEventCallback( FEventCallback aCallback )
{
    _eventProcessorFunction = aCallback;
}

// ------------------------------------------------------------

ost::FEventCallback ost::CWindow::EventCallbackFunction()
{
    return _eventProcessorFunction;
}

// ------------------------------------------------------------

void ost::CWindow::Close()
{
    _isOpen = false;
}

bool ost::CWindow::IsOpen() const
{
    return _isOpen;
}

ost::SUntypedPtr ost::CWindow::GetWindowPointer()
{
    return _winPtr;
}

// ------------------------------------------------------------

const ost::Vector2i& ost::CWindow::GetSize() const
{
    return _size;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
