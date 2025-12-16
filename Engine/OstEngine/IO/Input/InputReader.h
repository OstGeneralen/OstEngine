#pragma once
#include <OstEngine/IO/Input/KeyCodes.h>
#include <OstEngine/Types.h>
#include <bitset>

// ------------------------------------------------------------

namespace ost
{
    class CInputReader
    {
    public:
        bool ProcessInputEvent( Uint32 msg, Int64 w, Uint64 l );
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