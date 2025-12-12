#pragma once
#include <OstEngine/Types.h>

namespace ost
{
    namespace math
    {
        constexpr static Float32 RadToDeg = 180.0f / 3.141f;
        constexpr static Float32 DegToRad = 3.141f / 180.0f;

        struct Radians;

        struct Degrees
        {
            Degrees() = default;
            Degrees( const Degrees& ) = default;
            Degrees& operator=( const Degrees& ) = default;

            Degrees( Float32 v )
                : _value{ v }
            {
            }

            Degrees& operator=( Float32 v )
            {
                _value = v;
                return *this;
            }

            Float32 Get() const
            {
                return _value;
            }

            operator Radians() const
            {
                return { _value * DegToRad };
            }

        private:
            Float32 _value;
        };

        struct Radians
        {
            Radians() = default;
            Radians( const Radians& ) = default;
            Radians& operator=( const Radians& ) = default;
            Radians( Float32 v )
                : _value{ v }
            {
            }

            Radians& operator=( Float32 v )
            {
                _value = v;
                return *this;
            }

            Float32 Get() const
            {
                return _value;
            }

            operator Degrees() const
            {
                return { _value * RadToDeg };
            }

        private:
            Float32 _value;
        };
    } // namespace math
} // namespace ost