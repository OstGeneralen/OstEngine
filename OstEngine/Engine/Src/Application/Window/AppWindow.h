// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "Rendering/TextureRenderTarget.h"
#include "Subsystem/Input/InputEventProvider.h"

// ------------------------------------------------------------

struct GLFWwindow;

// ------------------------------------------------------------

namespace ost
{
	class CAppWindow
	{
	public:
		void Create(int w, int h, const char* t);
		void InitGUI();
		void Destroy();

		CTextureRenderTarget& GetWindowRenderBuffer();
		input::CInputEventProvider& GetInputEventProvider();

		bool ShouldRemainOpen() const;
		void PollEvents();

		void BeginWindowRenderFrame();
		void EndWindowRenderFrame();
	private:
		static void WindowKeyEvent(GLFWwindow* win, int kc, int sc, int a, int m);

	private:
		GLFWwindow* _winPtr{ nullptr };
		CTextureRenderTarget _windowRenderTarget;
		input::CInputEventProvider _inputEventProvider;
		bool _hasGUIInit{ false };
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------