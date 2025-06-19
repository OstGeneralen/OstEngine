// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"

#include <type_traits>
#include <concepts>
// ------------------------------------------------------------

namespace ost
{
	template<typename T>
	concept NumericType = std::is_same<ost::int32, T>::value || std::is_same<ost::uint32, T>::value
						|| std::is_same<ost::float32, T>::value
						|| std::is_same<ost::float64, T>::value;

	namespace num_util
	{
		constexpr static float32 flt32Tolerance = 0.0001f;
		constexpr static float64 flt64Tolerance = 0.0000001;

		template<typename T>
		static bool AreEqual(T a, T b) 
		{ 
			return a == b; 
		}

		template<>
		static bool AreEqual<float>(float a, float b)
		{
			return (a <= b + flt32Tolerance) && (a >= b - flt32Tolerance);
		}

		template<>
		static bool AreEqual<double>(double a, double b)
		{
			constexpr static double t = 0.0000001;
			return (a <= b + flt64Tolerance) && (a >= b - flt64Tolerance);
		}
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
