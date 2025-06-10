// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include "OstEngine/Application/Window/Window.h"

// ------------------------------------------------------------

namespace ost
{
	class CRenderingContext
	{
	public:
		CWindow* Initialize( int w, int h );
		void Release(CWindow** ppWindow);

		void BeginFrame();
		void EndFrame();
	private:
		void* _windowPtr;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------