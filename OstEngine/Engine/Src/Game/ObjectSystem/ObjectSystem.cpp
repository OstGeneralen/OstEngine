// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/ObjectSystem.h>
#include <OstEngine/Game/ObjectSystem/Objects/GameObjectHandle.h>

#include <cassert>

// ------------------------------------------------------------

ost::SGameObjectHandle ost::CGameObjectSystem::CreateObject()
{
	CGameObject& object = _objects.Emplace();
	return SGameObjectHandle(object.GetStableIndex(), *this);
}

// ------------------------------------------------------------

void ost::CGameObjectSystem::DestroyObject(SGameObjectHandle& handle)
{
	_objects.Remove(handle._objectStableIndex);

	// Invalidate the provided handle
	handle._objectStableIndex.Invalidate();
	handle._owningSystem = nullptr;
}

// ------------------------------------------------------------

ost::CGameObject& ost::CGameObjectSystem::GetObject(const SGameObjectHandle& h)
{
	assert(h.IsValid() && "Handle may not be invalid when getting object");
	return _objects.Get(h._objectStableIndex);
}

// ------------------------------------------------------------

const ost::CGameObject& ost::CGameObjectSystem::GetObject(const SGameObjectHandle& h) const
{
	assert(h.IsValid() && "Handle may not be invalid when getting object");
	return _objects.Get(h._objectStableIndex);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------