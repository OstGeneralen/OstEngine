// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/Application/Window/Window.h"

#include "Core/Input/InputSystem.h"

#include <glfw3.h>

// ------------------------------------------------------------

ost::CWindow::CWindow(GLFWwindow* winPtr)
	: _windowPtr(winPtr)
	, _inputSystemPtr(nullptr)
	, _open(true)
{
	glfwSetWindowUserPointer(winPtr, this);

}

// ------------------------------------------------------------

void ost::CWindow::Close()
{
	glfwDestroyWindow(_windowPtr);
	_windowPtr = nullptr;
}

// ------------------------------------------------------------

void ost::CWindow::ProcessEvents()
{
	if (_inputSystemPtr)
	{
		_inputSystemPtr->NewInputFrame();
	}
	glfwPollEvents();
}

// ------------------------------------------------------------

bool ost::CWindow::IsOpen() const
{
	return !glfwWindowShouldClose(_windowPtr);
}

// ------------------------------------------------------------

void ost::CWindow::BindInputSystem(input::CInputSystem* inputSystemPtr)
{
	_inputSystemPtr = inputSystemPtr;
	if (_inputSystemPtr != nullptr)
	{
		glfwSetKeyCallback(_windowPtr, InputEventCallback);
	}
}

// ------------------------------------------------------------

void ost::CWindow::InputEventCallback(GLFWwindow* wptr, int k, int sc, int a, int m)
{
	static_cast<CWindow*>(glfwGetWindowUserPointer(wptr))->OnInputEvent(k, sc, a, m);
}

// ------------------------------------------------------------

void ost::CWindow::OnInputEvent(int glfwKey, int scan, int action, int mod)
{
	input::EKey key = input::EKey::COUNT;

	// Translate input event
	if (glfwKey >= GLFW_KEY_A && glfwKey <= GLFW_KEY_Z)
	{
		const uint32 offset = glfwKey - GLFW_KEY_A;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::A) + offset);
	}
	else if (glfwKey >= GLFW_KEY_0 && glfwKey <= GLFW_KEY_9)
	{
		const uint32 offset = glfwKey - GLFW_KEY_0;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::Num0) + offset);
	}
	else if (glfwKey >= GLFW_KEY_KP_0 && glfwKey <= GLFW_KEY_KP_9)
	{
		const uint32 offset = glfwKey - GLFW_KEY_KP_0;
		key = static_cast<input::EKey>(static_cast<uint32>(input::EKey::NumPad0) + offset);
	}
	else
	{
		switch (glfwKey)
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
		_inputSystemPtr->NotifyKeyChange(key, action == GLFW_PRESS);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------