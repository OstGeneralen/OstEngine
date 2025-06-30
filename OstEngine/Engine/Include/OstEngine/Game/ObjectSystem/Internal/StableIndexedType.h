// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------

namespace ost
{
	// A stable indexed type must have at least one constructor that has a SStableIndex as its first argument
	class IStableIndexedType
	{
	public:
		IStableIndexedType() = default;
		virtual ~IStableIndexedType() = default;

		IStableIndexedType(SStableIndex id) : _stableID{ id } {}

		SStableIndex GetStableIdx() const { return _stableID; }
	private:
		SStableIndex _stableID;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------