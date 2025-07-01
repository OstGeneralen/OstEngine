// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Internal/StableIndexedTypeContainerBase.h>
#include <OstEngine/ObjectSystem/Internal/ComponentContainer.h>
#include <OstEngine/ObjectSystem/Component/ComponentsCore.h>

#include <type_traits>

// ------------------------------------------------------------

namespace ost
{
	// ------------------------------------------------------------
	// Generic base template type (actual qualified)
	// ------------------------------------------------------------
	template<StableIDMemberType T> 
	class TStableIndexedTypeContainer final : public CStableIndexedTypeContainerBase
	{
	public:
		template<typename ... TArgs>
		T& Emplace(TArgs&& ... args) { return Base_Emplace<T, TArgs...>(_denseList, std::forward(args)...); }

		void Remove(SStableIndex stableIndex) override { Base_Remove<T>(_denseList, stableIndex); }

		void Remove(T* ptrObj) { Base_Remove<T>(_denseList, ptrObj); }

		T& Get(SStableIndex stableIndex) { return Base_Get<T>(_denseList, stableIndex); }

		const T& Get(SStableIndex stableIndex) const { return Base_Get<T>(_denseList, stableIndex); }

		std::vector<T>& GetDense() { return _denseList; }
		const std::vector<T>& GetDense() const { return _denseList; }

	private:
		std::vector<T> _denseList;
	};

	// ------------------------------------------------------------
	// Specific component version (actual qualified)
	// ------------------------------------------------------------
	template<StableIDMemberType T> requires ComponentDerivedType<T>
	class TStableIndexedTypeContainer<T> final : public CComponentContainerBase
	{
	public:
		template<typename ... TArgs>
		T& Emplace(TArgs&& ... args) { return Base_Emplace<T, TArgs...>(_denseList, std::forward(args)...); }

		void Remove(SStableIndex stableIndex) override { Base_Remove<T>(_denseList, stableIndex); }

		void Remove(T* ptrObj) { Base_Remove<T>(_denseList, ptrObj); }

		T& Get(SStableIndex stableIndex) { return Base_Get<T>(_denseList, stableIndex); }

		const T& Get(SStableIndex stableIndex) const { return Base_Get<T>(_denseList, stableIndex); }

		std::vector<T>& GetDense() { return _denseList; }
		const std::vector<T>& GetDense() const { return _denseList; }

		// There isn't really a difference other than that for a ComponentDerivedType<T>
		// this implicit conversion is possible
		CComponent& GetComponent(SStableIndex stableIndex) override { return Base_Get<T>(_denseList, stableIndex); }
		const CComponent& GetComponent(SStableIndex stableIndex) const override { return Base_Get<T>(_denseList, stableIndex); }
		
		uint64 DenseComponentCount() const override
		{
			return _denseList.size();
		}
		CComponent& ComponentAtDenseIndex(uint64 denseIdx) override
		{
			return _denseList[denseIdx];
		}

	private:
		std::vector<T> _denseList;
	};

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------