// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------
// STABLE_IDX_TYPE utility macro
// ------------------------------------------------------------
// Simply place this macro in the body of your type to make
// it identifiable via a stable ID
// ------------------------------------------------------------
#define STABLE_IDX_TYPE(t) private: friend ost::TStableIndexedTypeContainer<t>; ost::SStableIndex _stableIndex
// ------------------------------------------------------------

namespace ost
{
	template<typename T> concept StableIDMemberType = requires(T t)
	{
		{ t._stableIndex } -> std::same_as<SStableIndex>;
	};

	// Forward declare of the container to allow friending in types
	template<StableIDMemberType T> class TStableIndexedTypeContainer;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------