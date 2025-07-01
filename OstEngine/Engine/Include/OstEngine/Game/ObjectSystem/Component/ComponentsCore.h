// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/StableIndexedType.h>

#include <typeinfo>

// ------------------------------------------------------------

namespace ost
{
	// ------------------------------------------------------------
	// ID for the unique Type of each component
	// ------------------------------------------------------------
	using ComponentTypeID_t = size_t;

	// ------------------------------------------------------------
	// Concept to ensure components derive from the base class
	// ------------------------------------------------------------
	class CComponent; template<typename T> concept ComponentDerivedType = std::is_base_of_v<CComponent, T>&& StableIDMemberType<T>;

	// ------------------------------------------------------------
	// Templated ComponentTypeID_t unique ID value
	// ------------------------------------------------------------
	template< ComponentDerivedType T > constexpr static ComponentTypeID_t ComponentTypeID = typeid(T).hash_code();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------