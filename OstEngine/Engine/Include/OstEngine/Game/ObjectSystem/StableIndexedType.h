// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------
// STABLE_IDX_TYPE utility macro
// ------------------------------------------------------------
// Simply place this macro in the body of your type to make
// it identifiable via a stable ID
// ------------------------------------------------------------
#define STABLE_IDX_CLASS_TYPE(t) private: ost::SStableIndex _stableIndex; public: ost::SStableIndex GetStableIndex() const { return _stableIndex; } void SetStableIndex(ost::SStableIndex idx) { _stableIndex = idx; } private:
#define STABLE_IDX_STRUCT_TYPE(t) private: ost::SStableIndex _stableIndex; public: ost::SStableIndex GetStableIndex() const { return _stableIndex; } void SetStableIndex(ost::SStableIndex idx) { _stableIndex = idx; }
// ------------------------------------------------------------

namespace ost
{
	template<typename T> concept StableIDMemberType = requires(T t)
	{
		{ t.GetStableIndex() } -> std::same_as<SStableIndex>;
		{ t.SetStableIndex(SStableIndex()) };
	};

	// Forward declare of the container to allow friending in types
	template<StableIDMemberType T> class TStableIndexedTypeContainer;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------