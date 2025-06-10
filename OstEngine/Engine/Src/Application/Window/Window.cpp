// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/Application/Window/Window.h"
#include <glfw3.h>


// ------------------------------------------------------------

ost::CWindow::CWindow(void* winPtr)
	: _windowPtr(winPtr)
	, _open(true)
{
}

// ------------------------------------------------------------

void ost::CWindow::Close()
{
	glfwDestroyWindow((GLFWwindow*)_windowPtr);
	_windowPtr = nullptr;
}

// ------------------------------------------------------------

void ost::CWindow::ProcessEvents()
{
	glfwPollEvents();
}

// ------------------------------------------------------------

bool ost::CWindow::IsOpen() const
{
	return !glfwWindowShouldClose((GLFWwindow*)_windowPtr);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------