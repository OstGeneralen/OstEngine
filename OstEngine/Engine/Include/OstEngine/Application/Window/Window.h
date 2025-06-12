// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>

// ------------------------------------------------------------

struct GLFWwindow;

namespace ost
{
	namespace input
	{
		class CInputSystem;
	}

	class CWindow
	{
	public:
		CWindow(GLFWwindow* winPtr);
		void Close();
		void ProcessEvents();
		bool IsOpen() const;

		void BindInputSystem(input::CInputSystem* inputSystemPtr);
	private:
		static void InputEventCallback(GLFWwindow* winPtr, int k, int sc, int a, int m);
		void OnInputEvent(int k, int sc, int a, int m);

		GLFWwindow* _windowPtr;
		input::CInputSystem* _inputSystemPtr;
		bool _open;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------