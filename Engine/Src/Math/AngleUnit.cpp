#include "OstEngine/Math/AngleUnit.h"

using namespace ost;
using namespace ost::math;

// ------------------------------------------------------------
// DEGREES
// ------------------------------------------------------------
Degrees::Degrees( const Radians& r )
    : _value{ r.Get() * RadToDeg }
{
}

Degrees::Degrees( Float32 v )
    : _value{ v }
{
}

Degrees& Degrees::operator=( const Radians& r )
{
    _value = r.Get() * RadToDeg;
    return *this;
}

void ost::math::Degrees::Set( Float32 aRadianValue )
{
    _value = aRadianValue;
}

Float32 Degrees::Get() const
{
    return _value;
}

// ------------------------------------------------------------
// RADIANS
// ------------------------------------------------------------

Radians::Radians( const Degrees& r )
    : _value{ r.Get() * DegToRad }
{
}

Radians::Radians( Float32 v )
    : _value{v}
{
}

Radians& Radians::operator=( const Degrees& r )
{
    _value = r.Get() * DegToRad;
    return *this;
}

void Radians::Set( Float32 aDegreeValue )
{
    _value = aDegreeValue;
}

Float32 Radians::Get() const
{
    return _value;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------