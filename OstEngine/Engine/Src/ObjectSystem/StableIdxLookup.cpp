// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/ManagedType/StableIdxLookup.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectType.h>

// ------------------------------------------------------------

ost::uint32 ost::CStableIdxLookup::GenerateStableIDX()
{
	uint32 generated = managed_type_constants::STABLE_IDX_INVALID;
	if (_recycledStableIdxs.empty())
	{
		generated = static_cast<uint32>(_denseIdxs.size());
		_denseIdxs.emplace_back(0);
	}
	else
	{
		generated = _recycledStableIdxs.front();
		_recycledStableIdxs.pop();
	}
	return generated;
}

// ------------------------------------------------------------

void ost::CStableIdxLookup::RecycleStableIDX(uint32 stableIdx)
{
	_recycledStableIdxs.push(stableIdx);
}

// ------------------------------------------------------------

ost::uint32 ost::CStableIdxLookup::StableToDenseIdx(uint32 stableIdx) const
{
	return _denseIdxs[stableIdx];
}

// ------------------------------------------------------------

void ost::CStableIdxLookup::MapStableToDenseIdx(uint32 stable, uint32 dense)
{
	_denseIdxs[stable] = dense;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------