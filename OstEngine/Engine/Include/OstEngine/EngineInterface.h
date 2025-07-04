// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Subsystem/IAssetsSystem.h>
#include <OstEngine/Subsystem/IInputSystem.h>

#include <OstEngine/ObjectSystem/Scene.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectPtr.h>

// ------------------------------------------------------------

namespace ost
{
	class IOstEngine
	{
	public:
		virtual TPtr<CScene> NewScene(bool makeActive) = 0;
		virtual void SetActiveScene(TPtr<CScene> scene) = 0;

		virtual IAssetsSystem& GetSystem_Assets() = 0;
		virtual input::IInputSystem& GetSystem_Input() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------