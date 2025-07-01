// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Component/Component.h>
#include <OstEngine/Math/Transform.h>

// ------------------------------------------------------------

namespace ost
{
	class CTransformComponent : public CComponent
	{
	public:
		CTransformComponent() = default;
		CTransformComponent(const CTransform& t) : Transform(t) {}

		CTransform Transform;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------