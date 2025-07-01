// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ObjectSystem.h>
#include <OstEngine/ObjectSystem/Objects/GameObjectHandle.h>
#include <OstEngine/Game/Core/TransformComponent.h>

#include <cassert>

// ------------------------------------------------------------

ost::CGameObjectSystem::CGameObjectSystem()
{
	// Register the core components
	_componentRegistry.RegisterComponentType<CTransformComponent>();
}

// ------------------------------------------------------------

ost::SGameObjectHandle ost::CGameObjectSystem::CreateObject()
{
	CGameObject& object = _objects.Emplace();
	SGameObjectHandle objectHandle{ object.GetStableIndex(), *this };

	_componentRegistry.EmplaceComponent<CTransformComponent>(objectHandle);

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

ost::CComponentRegistry& ost::CGameObjectSystem::ComponentsRegistry()
{
	return _componentRegistry;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------