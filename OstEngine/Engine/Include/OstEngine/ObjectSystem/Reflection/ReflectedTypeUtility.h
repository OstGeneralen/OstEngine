// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Utility/StringHashing.h>
#include <string_view>

namespace ost
{
	template<typename T>
	struct TReflectionData
	{
		constexpr static uint64 TypeUID = string_hash::HashString_64(T::OstCompReflection_Name);
		constexpr static std::string_view TypeName = T::OstCompReflection_Name;
	};
}