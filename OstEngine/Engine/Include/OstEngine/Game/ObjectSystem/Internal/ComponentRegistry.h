// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Component/Component.h>
#include <OstEngine/Game/ObjectSystem/Internal/StableIndexedTypeContainer.h>

#include <unordered_map>
#include <cassert>
#include <memory>

// ------------------------------------------------------------

namespace ost
{
	struct SComponentHandle;
	struct SGameObjectHandle;

	class CComponentRegistry
	{
	public:
		template<ComponentDerivedType T>
		void RegisterComponentType()
		{
			_registry[ComponentTypeID<T>] = std::make_unique<TStableIndexedTypeContainer<T>>();
		}

		template<ComponentDerivedType T, typename ... TArgs>
		SComponentHandle EmplaceComponent(SGameObjectHandle& onObject, TArgs&& ... args)
		{
			CComponentContainerBase* baseListPtr = GetComponentTypeList(ComponentTypeID<T>);
			
			assert(baseListPtr != nullptr && "Cannot emplace non-registered component type");

			TStableIndexedTypeContainer<T>* tListPtr = static_cast<TStableIndexedTypeContainer<T>*>(baseListPtr);
			T& created = tListPtr->Emplace(std::forward(args)...);
			const SComponentHandle componentHandle = GenerateComponentHandle(created.GetStableIndex(), ComponentTypeID<T>);
			AttachComponentToObject(onObject, componentHandle, created);
			return componentHandle;
		}

		template<ComponentDerivedType T> 
		T& GetComponent(const SComponentHandle& h)
		{
			return static_cast<T&>(GetComponent(h));
		}

		template<ComponentDerivedType T>
		std::vector<T>& GetAllComponentsOfType()
		{
			TStableIndexedTypeContainer<T>* l = static_cast<TStableIndexedTypeContainer*>(GetComponentTypeList(ComponentTypeID<T>));
			return l->GetDense();
		}

		template<ComponentDerivedType T>
		const std::vector<T>& GetAllComponentsOfType() const
		{
			const TStableIndexedTypeContainer<T>* l = static_cast<const TStableIndexedTypeContainer*>(GetComponentTypeList(ComponentTypeID<T>));
			return l->GetDense();
		}

		CComponent& GetComponent(const SComponentHandle& h);
	public:
		void TickComponents();
		void DestroyComponent(SComponentHandle& h);

	private:
		CComponentContainerBase* GetRegistryComponentTypeContainer(ComponentTypeID_t cTypeId);
		SComponentHandle GenerateComponentHandle(SStableIndex stableId, ComponentTypeID_t ctId);
		void AttachComponentToObject(SGameObjectHandle& hObject, const SComponentHandle& hComp, CComponent& compInstance);

		std::unordered_map< ComponentTypeID_t, std::unique_ptr<CComponentContainerBase>> _registry;

	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------