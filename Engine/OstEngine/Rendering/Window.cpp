#include "Window.h"

#include <SDL3/SDL.h>

// ------------------------------------------------------------

ost::CWindow::CWindow()
    : _winPtr{ nullptr }
    , _isOpen{false}
{
}

// ------------------------------------------------------------

ost::CWindow::CWindow( const char* aTitle, const Vector2i& aSize )
{
    _winPtr = SDL_CreateWindow( aTitle, aSize.X, aSize.Y, 0);
    _isOpen = _winPtr != nullptr;
}

// ------------------------------------------------------------

ost::CWindow::~CWindow()
{
    if ( _winPtr )
    {
        SDL_DestroyWindow( _winPtr );
        _winPtr = nullptr;
    }
}

// ------------------------------------------------------------

ost::CWindow::CWindow( CWindow&& aOther ) noexcept
    : _winPtr{ aOther._winPtr }
    , _isOpen{aOther._isOpen}
{
    aOther._winPtr = nullptr;
}

// ------------------------------------------------------------

ost::CWindow& ost::CWindow::operator=( CWindow&& aRhs ) noexcept
{
    _winPtr = aRhs._winPtr;
    aRhs._winPtr = nullptr;
    _isOpen = aRhs._isOpen;
    return *this;
}

// ------------------------------------------------------------

void ost::CWindow::RunEventLoop(CInputReader& aInputReader)
{
    SDL_Event e;
    while ( SDL_PollEvent( &e ) )
    {
        if (aInputReader.ProcessInputEvent(e))
        {
        }

        switch ( e.type )
        {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
            _isOpen = false;
            break;
        }
        }
    }
}

// ------------------------------------------------------------

bool ost::CWindow::IsOpen() const
{
    return _isOpen;
}

ost::SUntypedPtr ost::CWindow::GetWindowPointer()
{
    return _winPtr;
}

// ------------------------------------------------------------


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
