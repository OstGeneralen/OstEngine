// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>
#include <OstEngine/Game/ObjectSystem/StableIndexedType.h>

#include <vector>
#include <queue>

// ------------------------------------------------------------

namespace ost
{
	class CStableIndexedTypeContainerBase
	{
	public:
		virtual ~CStableIndexedTypeContainerBase() = default;

		virtual void Remove(SStableIndex id) = 0;
	protected:
		using DenseIndex_t = uint64;

		SStableIndex GenerateStableIndex();
		void RecycleStableIndex(SStableIndex id);

		void AssignStableIndexValue(SStableIndexInternalContainer& assignTo, SStableIndex assignVal);

		DenseIndex_t GetDenseIndex(SStableIndex stable) const;
		void StableToDenseIndexMap(SStableIndex stableIndex, DenseIndex_t denseIndex);

	private:
		std::vector<DenseIndex_t> _stableIDIndexList;
		std::queue<uint64> _recycledStableIDValues;

	protected: // FUNCTION IMPLS FOR SUB TYPES
		template<StableIDMemberType T, typename ... TArgs>
		T& Base_Emplace(std::vector<T>& denseList, TArgs&& ... args)
		{
			const SStableIndex stableID = GenerateStableIndex();
			T& created = denseList.emplace_back(args...);
			AssignStableIndexValue(created.GetSIDXContainer(), stableID);
			StableToDenseIndexMap(stableID, denseList.size() - 1);
			return created;
		}

		template<StableIDMemberType T>
		void Base_Remove(std::vector<T>& denseList, SStableIndex stable)
		{
			const uint64 removedInstanceDenseIdx = GetDenseIndex(stable);

			// Do a swap and pop removal if this is not the last element of the dense list
			if (removedInstanceDenseIdx != denseList.size() - 1)
			{
				// Swap the removed instance with the last of the dense list
				// We do this to maintain O(1) removal
				const SStableIndex movedElemStableIdx = denseList.back().GetStableIndex();
				std::swap(denseList.back(), denseList[removedInstanceDenseIdx]);

				// Since we have now moved a maintained element, update its mapped dense index
				StableToDenseIndexMap(movedElemStableIdx, removedInstanceDenseIdx);
			}

			// Now since the last element is the one we wish to remove we can simply pop-back and recycle the stable index
			denseList.pop_back();
			RecycleStableIndex(stable);
		}

		template<StableIDMemberType T>
		void Base_Remove(std::vector<T>& denseList, T* ptr)
		{
			Base_Remove<T>(denseList, ptr->GetStableIndex());
		}

		template<StableIDMemberType T>
		T& Base_Get(std::vector<T>& denseList, SStableIndex stable)
		{
			return denseList[GetDenseIndex(stable)];
		}

		template<StableIDMemberType T>
		const T& Base_Get(const std::vector<T>& denseList, SStableIndex stable) const
		{
			return denseList[GetDenseIndex(stable)];
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------