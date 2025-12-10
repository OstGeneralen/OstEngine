#pragma once
#include <OstEngine/Types.h>
#include <type_traits>
#include <concepts>

template <typename T>
concept FloatNumber = std::is_same<T, Float32>::value || std::is_same<T, Float64>::value;

namespace ost
{
	namespace NumericUtils
	{
		template<typename T>
		inline T Abs(T aValue)
		{
            return aValue < 0 ? -aValue : aValue;
		}

		template<FloatNumber T>
		inline bool NearlyEqual(const T aFirst, const T aSecond, const T aTolerance = static_cast<T>(0.00001f))
		{
            return Abs<T>(aFirst - aSecond) <= aTolerance;
		}
	}
}