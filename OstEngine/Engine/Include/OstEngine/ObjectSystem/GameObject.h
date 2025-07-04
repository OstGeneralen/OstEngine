// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectPtr.h>
#include <OstEngine/ObjectSystem/Component.h>
#include <string>
#include <vector>

namespace ost
{
	class CScene;
	class ISceneContent;

	class CGameObject
	{
		OST_MANAGED_TYPE

	public:
		static constexpr uint64 StaticUID = string_hash::HashString_64("GameObject");

	public:
		uint64 GetObjectID() const;
		uint32 GetObjectSceneStableIndex() const;
		uint32 GetObjectStableIndex() const;

		template<TOstComponentType T> 
		TPtr<T> GetComponent()
		{
			return TPtrCast::Static<CComponent, T>(GetComponentType(T::ReflectionData::TypeUID));
		}

		template<TOstComponentType T>
		TPtr<T> AddComponent()
		{
			return TPtrCast::Static<CComponent, T>(AddComponentType(T::ReflectionData::TypeUID));
		}

		template<TOstComponentType T>
		void RemoveComponent()
		{
			RemoveComponentType(T::ReflectionData::TypeUID);
		}
	private:
		friend class CScene;
		
		TPtr<CComponent> AddComponentType(uint64 componentType);
		void RemoveComponentType(uint64 componentType);
		TPtr<CComponent> GetComponentType(uint64 componentType);

		void FinishCreate(ISceneContent* sceneContentPtr, uint32 sceneID, std::string_view name);

		union GameObjectID
		{
			struct SplitData
			{
				uint16 ObjectID;
				uint16 SceneID;
				uint32 NameID;
			} Split;
			uint64 ID;
		} ObjectID;

		std::string _name;
		ISceneContent* _sceneContent;
		std::vector<TPtr<CComponent>> _components;
	};
}