// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "Subsystem/Input/InputSystem.h"

// ------------------------------------------------------------

namespace ost
{
	namespace input
	{
		class CInputEventProvider
		{
		public:
			void BindInputSystem(CInputSystem& is);
			void ReportKeyboardInput(int kc, int sc, int a, int m);
		private:
			CInputSystem* _inputSystemPtr{ nullptr };
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------