// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/System/InputReader.h"

using namespace ost;

// ------------------------------------------------------------

void InputReader::EndFrame()
{
    _keyboardState.previous = _keyboardState.current;
}

void InputReader::ProcessKeyEvent(EKeyboard key, bool state)
{
    _keyboardState.current[static_cast<SizeType>(key)] = state;
}

bool InputReader::Up(EKeyboard key) const
{
    return !Down(key);
}

bool InputReader::Down(EKeyboard key) const
{
    return _keyboardState.current[static_cast<SizeType>(key)];
}

bool InputReader::Pressed(EKeyboard key) const
{
    const SizeType kc = static_cast<SizeType>(key);
    return _keyboardState.current[kc] && !_keyboardState.previous[kc];
}

bool InputReader::Released(EKeyboard key) const
{
    const SizeType kc = static_cast<SizeType>(key);
    return !_keyboardState.current[kc] && _keyboardState.previous[kc];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------