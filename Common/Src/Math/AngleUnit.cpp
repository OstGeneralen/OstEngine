#include "OstEngine/Common/Math/AngleUnit.h"

// ------------------------------------------------------------
// DEGREES
// ------------------------------------------------------------

Degrees::Degrees( const Radians& r )
    : _value{ r.Get() * math::RadToDeg }
{
}

// ------------------------------------------------------------

Degrees::Degrees( Float32 v )
    : _value{ v }
{
}

// ------------------------------------------------------------

Degrees& Degrees::operator=( const Radians& r )
{
    _value = r.Get() * math::RadToDeg;
    return *this;
}

// ------------------------------------------------------------

void Degrees::Set( Float32 aRadianValue )
{
    _value = aRadianValue;
}

// ------------------------------------------------------------

Float32 Degrees::Get() const
{
    return _value;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------

// ------------------------------------------------------------
// RADIANS
// ------------------------------------------------------------

Radians::Radians( const Degrees& r )
    : _value{ r.Get() * math::DegToRad }
{
}

// ------------------------------------------------------------

Radians::Radians( Float32 v )
    : _value{ v }
{
}

// ------------------------------------------------------------

Radians& Radians::operator=( const Degrees& r )
{
    _value = r.Get() * math::DegToRad;
    return *this;
}

// ------------------------------------------------------------

void Radians::Set( Float32 aDegreeValue )
{
    _value = aDegreeValue;
}

// ------------------------------------------------------------

Float32 Radians::Get() const
{
    return _value;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------

// ------------------------------------------------------------
// Eulers
// ------------------------------------------------------------

EulerAngles::EulerAngles( Degrees aX, Degrees aY, Degrees aZ )
    : XAxis( aX )
    , YAxis( aY )
    , ZAxis( aZ )
{
}

// ------------------------------------------------------------

EulerAngles::EulerAngles( Radians aX, Radians aY, Radians aZ )
    : XAxis( aX )
    , YAxis( aY )
    , ZAxis( aZ )
{
}

// ------------------------------------------------------------

EulerAngles::EulerAngles( const ost::Vector3f& aEulers )
    : XAxis( aEulers.X )
    , YAxis( aEulers.Y )
    , ZAxis( aEulers.Z )
{
}

// ------------------------------------------------------------

ost::Vector3f EulerAngles::ToEulerVectorDegrees() const
{
    return { XAxis.Get(), YAxis.Get(), ZAxis.Get() };
}

ost::Vector3f EulerAngles::ToEulerVectorRadians() const
{
    return { Radians( XAxis ).Get(), Radians( YAxis ).Get(), Radians( ZAxis ).Get() };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------