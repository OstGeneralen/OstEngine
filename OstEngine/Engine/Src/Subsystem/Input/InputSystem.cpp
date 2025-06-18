// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Subsystem/Input/InputSystem.h"

// ------------------------------------------------------------

void ost::input::CInputSystem::NewInputFrame()
{
	switch (_currentState)
	{
	case 0: _currentState = 1; break;
	case 1: _currentState = 0; break;
	}

	KeyStateCurrent() = KeyStatePrevious();
}

// ------------------------------------------------------------

void ost::input::CInputSystem::NotifyKeyChange(EKey k, bool state)
{
	KeyStateCurrent()[static_cast<uint64>(k)] = state;
}

// ------------------------------------------------------------

bool ost::input::CInputSystem::KeyDown(EKey k) const
{
	return KeyStateCurrent()[static_cast<uint64>(k)];
}

// ------------------------------------------------------------

bool ost::input::CInputSystem::KeyUp(EKey k) const
{
	return !KeyDown(k);
}

// ------------------------------------------------------------

bool ost::input::CInputSystem::KeyPressed(EKey k) const
{
	return !KeyStatePrevious()[static_cast<uint64>(k)] && KeyDown(k);
}

// ------------------------------------------------------------

bool ost::input::CInputSystem::KeyReleased(EKey k) const
{
	return KeyStatePrevious()[static_cast<uint64>(k)] && KeyUp(k);
}

// ------------------------------------------------------------

ost::input::CInputSystem::KeyState& ost::input::CInputSystem::KeyStateCurrent()
{
	return _keyStateBuffer[_currentState];
}

// ------------------------------------------------------------

ost::input::CInputSystem::KeyState& ost::input::CInputSystem::KeyStatePrevious()
{
	switch (_currentState)
	{
	case 0: return _keyStateBuffer[1];
	default: return _keyStateBuffer[0];
	}
}

// ------------------------------------------------------------

const ost::input::CInputSystem::KeyState& ost::input::CInputSystem::KeyStateCurrent() const
{
	return _keyStateBuffer[_currentState];
}

// ------------------------------------------------------------

const ost::input::CInputSystem::KeyState& ost::input::CInputSystem::KeyStatePrevious() const
{
	switch (_currentState)
	{
	case 0: return _keyStateBuffer[1];
	default: return _keyStateBuffer[0];
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------