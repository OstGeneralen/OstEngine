#pragma once
#include <OstEngine/Application/KeyCodes.h>
#include <OstEngine/Types.h>
#include <bitset>

union SDL_Event;

// ------------------------------------------------------------

namespace ost
{
    class CInputReader
    {
    public:
        bool ProcessInputEvent( const SDL_Event& aEvent );
        void BeginFrame();

        bool IsKeyDown( EKeyCode aKey ) const;
        bool IsKeyUp( EKeyCode aKey ) const;
        bool KeyPressed( EKeyCode aKey ) const;
        bool KeyReleased( EKeyCode aKey ) const;

    private:
        std::bitset<Keycode::KeyCount> _previousStates;
        std::bitset<Keycode::KeyCount> _currentState;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------