// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Component/ComponentsCore.h>

#include <cassert>

// ------------------------------------------------------------

namespace ost
{
	struct SComponentHandle
	{
	public:
		template<ComponentDerivedType T>
		T& Get()
		{
			assert(ComponentTypeID<T> == _componentTypeID && "Get type T must match the component type");
			return static_cast<T&>(Get());
		}

		template<ComponentDerivedType T>
		T* GetPtr()
		{
			assert(ComponentTypeID<T> == _componentTypeID && "Get type T must match the component type");
			return &(static_cast<T&>(Get()));
		}

	public:
		SComponentHandle() = default;
		SComponentHandle(const SComponentHandle&) = default;
		SComponentHandle& operator=(const SComponentHandle&) = default;

		CComponent& Get();

		bool MatchComponentType(ComponentTypeID_t ctid) const;
		bool IsValid() const;

	private:
		friend class CComponentRegistry;

		SComponentHandle(SStableIndex sidx, ComponentTypeID_t ctid, CComponentRegistry& registry);
		void Invalidate();

		SStableIndex _componentStableIndex{};
		ComponentTypeID_t _componentTypeID{0};
		CComponentRegistry* _registryPtr{ nullptr };
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------