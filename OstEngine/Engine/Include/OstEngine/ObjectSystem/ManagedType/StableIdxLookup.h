// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>

#include <vector>
#include <queue>

// ------------------------------------------------------------

namespace ost
{
	class CStableIdxLookup
	{
	public:
		uint32 GenerateStableIDX();
		void RecycleStableIDX(uint32 stableIdx);
		uint32 StableToDenseIdx(uint32 stableIdx) const;

		void MapStableToDenseIdx(uint32 stable, uint32 dense);
	private:
		std::vector<uint32> _denseIdxs;
		std::queue<uint32> _recycledStableIdxs;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------