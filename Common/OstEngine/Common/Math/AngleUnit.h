#pragma once
#include <OstEngine/Types.h>
#include <OstEngine/Common/Math/Vector3.h>

// ------------------------------------------------------------

namespace math
{
    constexpr static Float32 RadToDeg = 180.0f / 3.141f;
    constexpr static Float32 DegToRad = 3.141f / 180.0f;
} // namespace math

// ------------------------------------------------------------

struct Radians;

struct Degrees
{
    Degrees() = default;
    Degrees( const Degrees& ) = default;
    Degrees( const Radians& r );
    Degrees( Float32 v );

    Degrees& operator=( const Degrees& ) = default;
    Degrees& operator=( const Radians& r );

    void Set( Float32 aRadianValue );
    Float32 Get() const;

private:
    Float32 _value;
};

// ------------------------------------------------------------

struct Radians
{
    Radians() = default;
    Radians( const Radians& ) = default;
    Radians( const Degrees& d );
    Radians( Float32 v );

    Radians& operator=( const Radians& ) = default;
    Radians& operator=( const Degrees& d );

    void Set( Float32 aRadianValue );
    Float32 Get() const;

private:
    Float32 _value;
};

// ------------------------------------------------------------

struct EulerAngles
{
    Degrees XAxis;
    Degrees YAxis;
    Degrees ZAxis;
    
    EulerAngles() = default;
    explicit EulerAngles( const EulerAngles& ) = default;
    EulerAngles& operator=( const EulerAngles& ) = default;
  
    EulerAngles( Radians aX, Radians aY, Radians aZ );
    EulerAngles( Degrees aX, Degrees aY, Degrees aZ );
    EulerAngles( const ost::Vector3f& aEulers );

    ost::Vector3f ToEulerVectorDegrees() const;
    ost::Vector3f ToEulerVectorRadians() const;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------