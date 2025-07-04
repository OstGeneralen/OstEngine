// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>
#include "OstEngine/Game/OstEngineGameCore.h"
#include <OstEngine/ObjectSystem/Registration/ComponentTypeRegistry.h>

// ------------------------------------------------------------

namespace ost
{
	class IGameInstance
	{
	public:
		virtual ~IGameInstance() = default;
		virtual std::string GameTitle() const = 0;

		virtual void RegisterGameComponents(CComponentTypeRegistry& registry) = 0;
		virtual void OnLoad() = 0;
		virtual void OnTick() = 0;
		virtual void OnUnload() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------