// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Subsystem/Input/InputEventProvider.h"

#include <glfw3.h>

// ------------------------------------------------------------

void ost::input::CInputEventProvider::BindInputSystem(CInputSystem& is)
{
	_inputSystemPtr = &is;
}

// ------------------------------------------------------------

void ost::input::CInputEventProvider::ReportKeyboardInput(int kc, int sc, int a, int m)
{
	if (_inputSystemPtr == nullptr) return;

	input::EKey key = input::EKey::COUNT;

	// Translate input event
	if (kc >= GLFW_KEY_A && kc <= GLFW_KEY_Z)
	{
		const uint32 offset = kc - GLFW_KEY_A;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::A) + offset);
	}
	else if (kc >= GLFW_KEY_0 && kc <= GLFW_KEY_9)
	{
		const uint32 offset = kc - GLFW_KEY_0;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::Num0) + offset);
	}
	else if (kc >= GLFW_KEY_KP_0 && kc <= GLFW_KEY_KP_9)
	{
		const uint32 offset = kc - GLFW_KEY_KP_0;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::NumPad0) + offset);
	}
	else
	{
		switch (kc)
		{
		case GLFW_KEY_SPACE: key = input::EKey::Space; break;
		case GLFW_KEY_LEFT_CONTROL: key = input::EKey::LCtrl; break;
		case GLFW_KEY_RIGHT_CONTROL: key = input::EKey::RCtrl; break;
		case GLFW_KEY_LEFT_ALT: key = input::EKey::LAlt; break;
		case GLFW_KEY_RIGHT_ALT: key = input::EKey::RAlt; break;
		case GLFW_KEY_BACKSPACE: key = input::EKey::Backspace; break;
		}
	}

	if (key != input::EKey::COUNT)
	{
		_inputSystemPtr->NotifyKeyChange(key, a == GLFW_PRESS);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------