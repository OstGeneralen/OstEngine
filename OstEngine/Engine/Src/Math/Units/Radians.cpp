// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Math/Units/Radians.h"

#include "OstEngine/Math/Units/Degrees.h"
#include "OstEngine/Math/CommonMath.h"
#include "OstEngine/Math/MathUtils.h"

// ------------------------------------------------------------

ost::Radians::Radians()
	: _value{0.0f}
{
}

// ------------------------------------------------------------

ost::Radians::Radians(float32 v)
	: _value{v}
{
}

// ------------------------------------------------------------

ost::Radians::Radians(const Degrees& d)
	: _value{d.Get() * math::constants::DEG_TO_RAD<float32>}
{
}

// ------------------------------------------------------------

ost::Radians::operator Degrees() const
{
	return Degrees{ _value * math::constants::RAD_TO_DEG<float32> };
}

// ------------------------------------------------------------

ost::float32 ost::Radians::Get() const
{
	return _value;
}

// ------------------------------------------------------------

bool ost::Radians::operator==(Radians r)
{
	return num_util::AreEqual<float32>(_value, r._value);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
