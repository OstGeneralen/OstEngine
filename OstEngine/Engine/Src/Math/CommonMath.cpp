// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Math/CommonMath.h"
#include <cmath>

// ------------------------------------------------------------

ost::float32 ost::math::Sin(Radians r)
{
	return sinf(r.Get());
}

// ------------------------------------------------------------

ost::float32 ost::math::Cos(Radians r)
{
	return cosf(r.Get());
}

// ------------------------------------------------------------

ost::float32 ost::math::Tan(Radians r)
{
	return tanf(r.Get());
}

// ------------------------------------------------------------

ost::float32 ost::math::Sqrt(float32 v)
{
	return sqrtf(v);
}

// ------------------------------------------------------------

ost::float64 ost::math::Sqrt(float64 v)
{
	return sqrt(v);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------