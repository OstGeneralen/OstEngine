// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Component.h>
#include <OstEngine/Math/Transform.h>
#include <OstEngine/ObjectSystem/Reflection/ReflectedTypeUtility.h>

// ------------------------------------------------------------

namespace ost
{
	class CTransformComponent : public CComponent
	{
	public: 
		OST_COMPONENT(CTransformComponent)

	public:
		CTransformComponent() = default;
		CTransform Transform;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------