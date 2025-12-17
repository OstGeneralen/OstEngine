#include "OstEngine/Math/AngleUnit.h"

using namespace ost;
using namespace ost::math;

// ------------------------------------------------------------
// DEGREES
// ------------------------------------------------------------
inline Degrees::Degrees( const Radians& r )
    : _value{ r.Get() * RadToDeg }
{
}

Degrees::Degrees( Float32 v )
    : _value{ v }
{
}

inline Degrees& Degrees::operator=( const Radians& r )
{
    _value = r.Get() * RadToDeg;
}

void ost::math::Degrees::Set( Float32 aRadianValue )
{
    _value = aRadianValue;
}

inline Float32 Degrees::Get() const
{
    return _value;
}

// ------------------------------------------------------------
// RADIANS
// ------------------------------------------------------------

inline Radians::Radians( const Degrees& r )
    : _value{ r.Get() * DegToRad }
{
}

Radians::Radians( Float32 v )
    : _value{v}
{
}

inline Radians& Radians::operator=( const Degrees& r )
{
    _value = r.Get() * DegToRad;
}

void Radians::Set( Float32 aDegreeValue )
{
    _value = aDegreeValue;
}

inline Float32 Radians::Get() const
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------