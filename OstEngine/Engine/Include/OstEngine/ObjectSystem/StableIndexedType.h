// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------
// STABLE_IDX_TYPE utility macro
// ------------------------------------------------------------
// Simply place this macro in the body of your type to make
// it identifiable via a stable ID
// ------------------------------------------------------------

#define STABLE_IDX_STRUCT_TYPE private: ost::SStableIndexInternalContainer _sIdxC; public: ost::SStableIndex GetStableIndex() const { return _sIdxC.Get(); } ost::SStableIndexInternalContainer& GetSIDXContainer() { return _sIdxC; }
#define STABLE_IDX_CLASS_TYPE STABLE_IDX_STRUCT_TYPE private:
// ------------------------------------------------------------

namespace ost
{
	// ------------------------------------------------------------
	// Internal and well protected type that contains a stable idx
	// which can only be mutated by a Stable Indexed Type Container
	// ------------------------------------------------------------
	struct SStableIndexInternalContainer
	{
		SStableIndex Get() const { return _index; }
	private:
		friend class CStableIndexedTypeContainerBase;
		SStableIndex _index;
	};

	// ------------------------------------------------------------
	// Concept ensuring correct setup of any stable idx type
	// Easiest way is to use the STABLE_IDX_..._TYPE macros to
	// make one, but allows user to implement it themselves as long
	// as the required functions are provided via the public API.
	// ------------------------------------------------------------
	template<typename T> concept StableIDMemberType = requires(T t)
	{
		{ t.GetStableIndex() } -> std::same_as<SStableIndex>;
		{ t.GetSIDXContainer() } -> std::same_as<SStableIndexInternalContainer&>;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------