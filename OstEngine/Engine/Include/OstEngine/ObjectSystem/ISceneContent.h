// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>

namespace ost
{
	class CComponent;
	class CGameObject;
	class CManagedTypeContainerBase;
	class CManagedTypeContainerBase_Component;

	class ISceneContent
	{
	public:
		virtual CGameObject& GetObject(uint32 objectStableIndex) = 0;
		virtual uint32 NewComponent(uint64 typeID) = 0;
		virtual CComponent& GetComponent(uint64 typeID, uint32 stableIndex) = 0;
		virtual void RemoveComponent(uint64 typeID, uint32 stableIndex) = 0;

		virtual CManagedTypeContainerBase_Component* GetContainerForComponentType(uint64 componentTypeID) = 0;
	};
}