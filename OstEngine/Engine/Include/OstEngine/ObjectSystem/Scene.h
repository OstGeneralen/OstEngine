// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedTypeContainer.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectPtr.h>
#include <OstEngine/ObjectSystem/GameObject.h>
#include <OstEngine/ObjectSystem/Registration/ComponentTypeRegistry.h>
#include <OstEngine/ObjectSystem/ISceneContent.h>

#include <unordered_map>

namespace ost
{
	class CScene : public ISceneContent
	{
		OST_MANAGED_TYPE
	public:
		static constexpr uint64 StaticUID = string_hash::HashString_64("Scene");
	public:
		CScene(CComponentTypeRegistry& registry);
		TPtr<CGameObject> CreateObject(std::string_view objectName = "");

		void Tick();
	private:
		TManagedTypeContainer<CGameObject> _objects;
		std::unordered_map<uint64, CManagedTypeContainerBase_Component*> _componentLists;
		
	private: // ISceneContent
		// Kept private in spite of being interface methods due to this being internal complexities
		CGameObject& GetObject(uint32 objectStableIndex) override;
		uint32 NewComponent(uint64 typeID) override;
		CComponent& GetComponent(uint64 typeID, uint32 stableIndex) override;
		void RemoveComponent(uint64 typeID, uint32 stableIndex) override {};

		CManagedTypeContainerBase_Component* GetContainerForComponentType(uint64 componentTypeID) override;
	};
}