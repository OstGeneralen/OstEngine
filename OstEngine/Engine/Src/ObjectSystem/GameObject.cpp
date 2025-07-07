// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/GameObject.h>
#include <OstEngine/ObjectSystem/ISceneContent.h>

#include <algorithm>

// ------------------------------------------------------------

ost::TPtr<ost::CComponent> ost::CGameObject::AddComponentType(uint64 componentType)
{
	CManagedTypeContainerBase_Component* containerPtr = _sceneContent->GetContainerForComponentType(componentType);
	CComponent& c = containerPtr->NewComponent();
	c._ownerObjectID = Internal_GetMOD().GetStableIndex();
	c._sceneContent = _sceneContent;

	return TPtr<CComponent>( c.Internal_GetMOD().GetStableIndex(), containerPtr );
}

// ------------------------------------------------------------

ost::TPtr<ost::CComponent> ost::CGameObject::GetComponentType(uint64 componentType)
{
	auto it = std::find_if(_components.begin(), _components.end(), [componentType](const TPtr<CComponent>& p) {  return p.MatchContainerStorageTypeID(componentType); });
	if (it != _components.end())
	{
		return *it;
	}
	return TPtr<CComponent>();
}

// ------------------------------------------------------------

void ost::CGameObject::RemoveComponentType(uint64 componentType)
{
	auto it = std::erase_if(_components, [componentType](const TPtr<CComponent>& p) {  return p.MatchContainerStorageTypeID(componentType); });
}

// ------------------------------------------------------------

ost::uint64 ost::CGameObject::GetObjectID() const
{
	return ObjectID.ID;
}

// ------------------------------------------------------------

ost::uint32 ost::CGameObject::GetObjectSceneStableIndex() const
{
	return static_cast<uint32>(ObjectID.Split.SceneID);
}

// ------------------------------------------------------------

ost::uint32 ost::CGameObject::GetObjectStableIndex() const
{
	return static_cast<uint32>(ObjectID.Split.ObjectID);
}

// ------------------------------------------------------------

void ost::CGameObject::FinishCreate(ISceneContent* sceneContentPtr, uint32 sceneID, std::string_view name)
{
	_sceneContent = sceneContentPtr;
	ObjectID.Split.SceneID = static_cast<uint16>(sceneID);
	ObjectID.Split.ObjectID = static_cast<uint16>(Internal_GetMOD().GetStableIndex());
	ObjectID.Split.NameID = string_hash::HashString_32(name);
	_name = name;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------