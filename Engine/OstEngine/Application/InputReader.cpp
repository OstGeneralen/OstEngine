#include "InputReader.h"

#include <SDL3/SDL.h>

#define KEY_CODE_INDEX( kc ) static_cast<Uint8>(kc)

// ------------------------------------------------------------

bool ost::CInputReader::ProcessInputEvent( const SDL_Event& aEvent )
{
    const EKeyCode engineKeyCode = Keycode::ConvertVirtualKC( aEvent.key.key );
    if ( engineKeyCode == EKeyCode::Unknown )
        return false;

    const Uint8 kcIdx = static_cast<Uint8>( engineKeyCode );

    switch ( aEvent.type )
    {
    case SDL_EventType::SDL_EVENT_KEY_DOWN: {
        _currentState[kcIdx] = true;
        break;
    }
    case SDL_EventType::SDL_EVENT_KEY_UP: {
        _currentState[kcIdx] = false;
        break;
    }
    }

    return true;
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