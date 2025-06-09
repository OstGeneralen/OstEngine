// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/Application/Window/Window.h"
#include <unordered_map>

std::unordered_map<void*, ost::CWindow*> WinInstances;

ost::CWindow& GetInstance(void* handle) { return *WinInstances.at(handle); }



#if _WIN32
#include <Windows.h>
LRESULT CALLBACK WindowProc(HWND winHandle, UINT message, WPARAM wParam, LPARAM  lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		GetInstance(winHandle).Close();
	}

	return DefWindowProc(winHandle, message, wParam, lParam);
}

// ------------------------------------------------------------

void ost::CWindow::Create(const SWindowSettings& settings)
{
	// Create Window Class
	WNDCLASSEX windowClass{};
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = (HINSTANCE)settings.InstanceInfo;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszClassName = "OstEngineWindowClass";

	RegisterClassEx(&windowClass);

	// Create Window
	HWND winHandle = CreateWindowEx(
		NULL,
		"OstEngineWindowClass",
		settings.Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		settings.Width, settings.Height,
		NULL,
		NULL,
		(HINSTANCE)settings.InstanceInfo,
		NULL
	);

	_winHandle = winHandle;
	WinInstances[winHandle] = this;
	ShowWindow(winHandle, settings.InstanceFlags);
	_open = true;

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	RecalcDPIAwareSize();
}

// ------------------------------------------------------------

void ost::CWindow::ProcessEvents()
{
	MSG msg;
	while (PeekMessage(&msg, (HWND)_winHandle, 0, 0, TRUE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// ------------------------------------------------------------

void ost::CWindow::Close()
{
	_open = false;
}

// ------------------------------------------------------------

bool ost::CWindow::IsOpen() const
{
	return _open;
}

// ------------------------------------------------------------

void ost::CWindow::RecalcDPIAwareSize()
{
	RECT logicalSizeRect{};
	GetClientRect((HWND)_winHandle, &logicalSizeRect);
	auto windowDpi = GetDpiForWindow((HWND)_winHandle);

	_w = (logicalSizeRect.right - logicalSizeRect.left) * (windowDpi / 96);
	_h = (logicalSizeRect.bottom - logicalSizeRect.top) * (windowDpi / 96);
}

#endif

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------