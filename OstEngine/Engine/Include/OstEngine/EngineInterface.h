// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Subsystem/IAssetsSystem.h>
#include <OstEngine/Subsystem/IInputSystem.h>

// ------------------------------------------------------------

namespace ost
{
	class IOstEngine
	{
	public:
		virtual IAssetsSystem& GetSystem_Assets() = 0;
		virtual input::IInputSystem& GetSystem_Input() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------