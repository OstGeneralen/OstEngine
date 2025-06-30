// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>

#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>
#include <OstEngine/Game/ObjectSystem/Internal/StableIndexedType.h>

#include <vector>
#include <queue>

// ------------------------------------------------------------

namespace ost
{
	template<typename T> concept TypeWithStableID = std::is_base_of_v<IStableIndexedType, T>;

	// ------------------------------------------------------------
	// Base Type
	// ------------------------------------------------------------
	class CStableIndexedTypeContainerBase
	{
	public:
		virtual ~CStableIndexedTypeContainerBase() = default;

		virtual void Remove(SStableIndex id) = 0;

	protected:
		using DenseIndex_t = uint64;

		SStableIndex GenerateStableIndex();
		void RecycleStableIndex(SStableIndex id);

		DenseIndex_t GetDenseIndex(SStableIndex stable) const;
		void StableToDenseIndexMap(SStableIndex stableIndex, DenseIndex_t denseIndex);
	private:
		std::vector<DenseIndex_t> _stableIDIndexList;
		std::queue<uint64> _recycledStableIDValues;
	};

	// ------------------------------------------------------------
	// Templated Type (actual qualified)
	// ------------------------------------------------------------
	template<TypeWithStableID T>
	class TStableIndexedTypeContainer final : public CStableIndexedTypeContainerBase
	{
	public:
		template<typename ... TArgs>
		T& Emplace(TArgs&& ... args)
		{
			const SStableIndex stableID = GenerateStableIndex();
			_denseList.emplace_back(args...);
			StableToDenseIndexMap(stableID, _denseList.size() - 1);
			return _denseList[GetDenseIndex(stableID)];
		}

		void Remove(SStableIndex stableIndex) override
		{
			const uint64 removedInstanceDenseIdx = GetDenseIndex(stableIndex);

			// Do a swap and pop removal if this is not the last element of the dense list
			if (removedInstanceDenseIdx != _denseList.size() - 1)
			{
				// Swap the removed instance with the last of the dense list
				// We do this to maintain O(1) removal
				const SStableIndex movedElemStableIdx = static_cast<IStableIndexedType&>(_denseList.back()).GetStableIdx();
				std::swap(_denseList.back(), _denseList[removedInstanceDenseIdx]);

				// Since we have now moved a maintained element, update its mapped dense index
				StableToDenseIndexMap(movedElemStableIdx, removedInstanceDenseIdx);
			}

			// Now since the last element is the one we wish to remove we can simply pop-back and recycle the stable index
			_denseList.pop_back();
			RecycleStableIndex(stableIndex);
		}

		void Remove(T* ptrObj)
		{
			// This cast isn't strictly necessary but helps intellisense track
			// the type so leaving it here since it's static anyway
			Remove(static_cast<IStableIndexedType*>(ptrObj)->GetStableIdx());
		}

		T& Get(SStableIndex stableIndex)
		{
			return _denseList[GetDenseIndex(stableIndex)];
		}

		const T& Get(SStableIndex stableIndex) const
		{
			return _denseList[GetDenseIndex(stableIndex)];
		}

	private:
		std::vector<T> _denseList;
	};

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------