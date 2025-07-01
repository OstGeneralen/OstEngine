// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson(MIT License)
#include <OstEngine/Game/ObjectSystem/Component/Component.h>

// ------------------------------------------------------------

ost::CGameObject& ost::CComponent::GetOwner()
{
	return _hObject.GetObject();
}

// ------------------------------------------------------------

const ost::CGameObject& ost::CComponent::GetOwner() const
{
	return _hObject.GetObject();
}

// ------------------------------------------------------------

bool ost::CComponent::ShouldTick() const
{
	return _shouldTick;
}

// ------------------------------------------------------------

void ost::CComponent::SetShouldTick(bool shouldTick)
{
	_shouldTick = shouldTick;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------