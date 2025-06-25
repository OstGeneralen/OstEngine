// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Math/Units/Degrees.h"

#include "OstEngine/Math/Units/Radians.h"
#include "OstEngine/Math/CommonMath.h"
#include "OstEngine/Math/MathUtils.h"

// ------------------------------------------------------------

ost::Degrees::Degrees()
	: _value{0}
{
}

// ------------------------------------------------------------

ost::Degrees::Degrees(float32 v)
	: _value{v}
{
}

// ------------------------------------------------------------

ost::Degrees::Degrees(const Radians& d)
	: _value{d.Get() * math::constants::RAD_TO_DEG<float32>}
{
}

// ------------------------------------------------------------

//ost::Degrees::operator Radians() const
//{
//	return Radians{ _value * math::constants::DEG_TO_RAD<float32> };
//}

// ------------------------------------------------------------

ost::float32 ost::Degrees::Get() const
{
	return _value;
}

// ------------------------------------------------------------

bool ost::Degrees::operator==(Degrees d)
{
	return num_util::AreEqual<float32>(_value, d._value);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------