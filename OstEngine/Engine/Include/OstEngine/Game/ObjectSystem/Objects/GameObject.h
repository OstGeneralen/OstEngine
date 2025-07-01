// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson(MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/StableIndexedType.h>
#include <OstEngine/Game/ObjectSystem/Component/ComponentHandle.h>

#include <vector>
#include <cassert>

// ------------------------------------------------------------

namespace ost
{
	class CGameObject
	{
		STABLE_IDX_CLASS_TYPE
	public:
		template<ComponentDerivedType T>
		T* TryGetComponent()
		{
			SComponentHandle* h = TryGetComponentHandle(ComponentTypeID<T>);
			return h != nullptr ? h->GetPtr<T>() : nullptr;
		}

		template<ComponentDerivedType T>
		const T* TryGetComponent() const
		{
			const SComponentHandle* h = TryGetComponentHandle(ComponentTypeID<T>);
			return h != nullptr ? h->GetPtr<T>() : nullptr;
		}

		template<ComponentDerivedType T>
		T& GetComponent()
		{
			T* compPtr = TryGetComponent<T>();
			assert(compPtr != nullptr && "GetComponent must find a component of the given type. Use TryGetComponent instead or check HasComponent first.");
			return *compPtr;
		}

		template<ComponentDerivedType T>
		const T& GetComponent() const
		{
			const T* compPtr = TryGetComponent<T>();
			assert(compPtr != nullptr && "GetComponent must find a component of the given type. Use TryGetComponent instead or check HasComponent first.");
			return *compPtr;
		}

		template<ComponentDerivedType T>
		bool HasComponent() const
		{
			return TryGetComponent<T>() != nullptr;
		}

	private:
		SComponentHandle* TryGetComponentHandle(ComponentTypeID_t compTypeID);
		const SComponentHandle* TryGetComponentHandle(ComponentTypeID_t compTypeID) const;

		friend class CComponentRegistry;
		std::vector<SComponentHandle> _components;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
