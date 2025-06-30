// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Game/ObjectSystem/Internal/StableIndexedTypeContainer.h>
#include <cassert>

// ------------------------------------------------------------

inline ost::SStableIndex ost::CStableIDTypeContainerBase::GenerateStableIndex()
{
	if (_recycledStableIDValues.empty() == false)
	{
		const SStableIndex stableIdx { _recycledStableIDValues.front() };
		_recycledStableIDValues.pop();
		return stableIdx;
	}

	_stableIDIndexList.emplace_back(0);
	return SStableIndex{ _stableIDIndexList.size() - 1 };
}

// ------------------------------------------------------------

void ost::CStableIDTypeContainerBase::RecycleStableIndex(SStableIndex id)
{
	_recycledStableIDValues.push(id.Get());
}

// ------------------------------------------------------------

ost::CStableIDTypeContainerBase::DenseIndex_t ost::CStableIDTypeContainerBase::GetDenseIndex(SStableIndex stable) const
{
	assert(stable.IsValid() && "Invalid stable index is not allowed");
	return _stableIDIndexList[stable.Get()];
}

// ------------------------------------------------------------

void ost::CStableIDTypeContainerBase::StableToDenseIndexMap(SStableIndex stableIndex, DenseIndex_t denseIndex)
{
	_stableIDIndexList[stableIndex.Get()] = denseIndex;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------