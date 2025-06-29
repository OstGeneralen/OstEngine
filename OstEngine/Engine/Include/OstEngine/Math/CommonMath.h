// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/Units/Radians.h"
#include "OstEngine/Math/Units/Degrees.h"

// ------------------------------------------------------------

namespace ost
{
	namespace math
	{
		namespace constants
		{
			template<typename T>
			constexpr static T UNSUPPORTED_CONSTANT_TYPE() { static_assert(false); }

			template<typename T> constexpr static T PI = UNSUPPORTED_CONSTANT_TYPE<T>();
			template<> constexpr static float32 PI<float32> = 3.1416f;
			template<> constexpr static float64 PI<float64> = 3.141592;

			template<typename T> constexpr static T DEG_TO_RAD = UNSUPPORTED_CONSTANT_TYPE<T>();
			template<> constexpr static float32 DEG_TO_RAD<float32> = PI<float32> / 180.0f;
			template<> constexpr static float64 DEG_TO_RAD<float64> = PI<float64> / 180.0;

			template<typename T> constexpr static T RAD_TO_DEG = UNSUPPORTED_CONSTANT_TYPE<T>();
			template<> constexpr static float32 RAD_TO_DEG<float32> = 180.0f / PI<float32>;
			template<> constexpr static float64 RAD_TO_DEG<float64> = 180.0 / PI<float64>;
		}

		extern float32 Sin(Radians r);
		extern float32 Cos(Radians r);
		extern float32 Tan(Radians r);

		extern float32 Sqrt(float32 v);
		extern float64 Sqrt(float64 v);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------