// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------
// STABLE_IDX_TYPE utility macro
// ------------------------------------------------------------
// Simply place this macro in the body of your type to make
// it identifiable via a stable ID
// ------------------------------------------------------------
#define STABLE_IDX_CLASS_TYPE(t) private: ost::SStableIndex _stableIndex; public: ost::SStableIndex GetStableIndex() const { return _stableIndex; } private: friend ost::TStableIndexedTypeContainer<t>;
#define STABLE_IDX_STRUCT_TYPE(t) private: ost::SStableIndex _stableIndex; public: ost::SStableIndex GetStableIndex() const { return _stableIndex; } private: friend ost::TStableIndexedTypeContainer<t>; public:
// ------------------------------------------------------------

namespace ost
{
	template<typename T> concept StableIDMemberType = requires(T t)
	{
		{ t.GetStableIndex() } -> std::same_as<SStableIndex>;
	};

	// Forward declare of the container to allow friending in types
	template<StableIDMemberType T> class TStableIndexedTypeContainer;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------