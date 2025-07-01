// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson(MIT License)
#include <OstEngine/Game/ObjectSystem/Objects/GameObject.h>

#include <algorithm>


// ------------------------------------------------------------

ost::SComponentHandle* ost::CGameObject::TryGetComponentHandle(ComponentTypeID_t compTypeID)
{
	std::vector<SComponentHandle>::iterator it = std::find_if(_components.begin(), _components.end(), [&](const SComponentHandle& h) { return h.MatchComponentType(compTypeID); });
	if (it == _components.end())
	{
		return nullptr;
	}
	return &(*it);
}

// ------------------------------------------------------------

const ost::SComponentHandle* ost::CGameObject::TryGetComponentHandle(ComponentTypeID_t compTypeID) const
{
	std::vector<SComponentHandle>::const_iterator it = std::find_if(_components.begin(), _components.end(), [&](const SComponentHandle& h) { return h.MatchComponentType(compTypeID); });
	if (it == _components.end())
	{
		return nullptr;
	}
	return &(*it);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------