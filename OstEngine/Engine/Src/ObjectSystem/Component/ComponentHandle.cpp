// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/Component/ComponentHandle.h>

#include <OstEngine/ObjectSystem/Internal/ComponentRegistry.h>

// ------------------------------------------------------------

ost::SComponentHandle::SComponentHandle(SStableIndex sidx, ComponentTypeID_t ctid, CComponentRegistry& registry)
	: _componentStableIndex{sidx}
	, _componentTypeID{ctid}
	, _registryPtr{&registry}
{
}

// ------------------------------------------------------------

ost::CComponent& ost::SComponentHandle::Get()
{
	return _registryPtr->GetComponent(*this);
}

// ------------------------------------------------------------

bool ost::SComponentHandle::MatchComponentType(ComponentTypeID_t ctid) const
{
	return _componentTypeID == ctid;
}

// ------------------------------------------------------------

bool ost::SComponentHandle::IsValid() const
{
	return _registryPtr != nullptr && _componentStableIndex.IsValid();
}

// ------------------------------------------------------------

void ost::SComponentHandle::Invalidate()
{
	_registryPtr = nullptr;
	_componentStableIndex.Invalidate();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------