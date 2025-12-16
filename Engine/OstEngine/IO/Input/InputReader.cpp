#include "InputReader.h"

#include <Windows.h>

#define KEY_CODE_INDEX( kc ) static_cast<Uint8>(kc)

// ------------------------------------------------------------

bool ost::CInputReader::ProcessInputEvent( Uint32 msg, Int64 w, Uint64 l )
{
    const EKeyCode engineKeyCode = Keycode::ConvertVirtualKC( w );
    if ( engineKeyCode == EKeyCode::Unknown )
        return false;

    const Uint8 kcIdx = static_cast<Uint8>( engineKeyCode );
    switch ( msg )
    {
    case WM_KEYDOWN:
        _currentState[kcIdx] = true;
        return true;
    case WM_KEYUP:
        _currentState[kcIdx] = false;
        return true;
    }

    return false;
}

// ------------------------------------------------------------

void ost::CInputReader::BeginFrame()
{
    _previousStates = _currentState;
}

// ------------------------------------------------------------

bool ost::CInputReader::IsKeyDown( EKeyCode aKey ) const
{
    return _currentState[KEY_CODE_INDEX(aKey)];
}

// ------------------------------------------------------------

bool ost::CInputReader::IsKeyUp( EKeyCode aKey ) const
{
    return !_currentState[KEY_CODE_INDEX(aKey)];
}

// ------------------------------------------------------------

bool ost::CInputReader::KeyPressed( EKeyCode aKey ) const
{
    return _currentState[KEY_CODE_INDEX( aKey )] && !_previousStates[KEY_CODE_INDEX(aKey)];
}

// ------------------------------------------------------------

bool ost::CInputReader::KeyReleased( EKeyCode aKey ) const
{
    return !_currentState[KEY_CODE_INDEX( aKey )] && _previousStates[KEY_CODE_INDEX( aKey )];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------