// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Component.h>

#include <string>

// ------------------------------------------------------------

namespace ost
{
	class CNameComponent : public CComponent
	{
		OST_COMPONENT(CNameComponent)
	public:
		CNameComponent() = default;

		void Tick();

		std::string Name;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------