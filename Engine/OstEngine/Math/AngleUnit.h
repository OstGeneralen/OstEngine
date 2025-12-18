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
            Degrees( const Radians& r );
            Degrees( Float32 v );

            Degrees& operator=( const Degrees& ) = default;
            Degrees& operator=( const Radians& r );
            
            void Set( Float32 aRadianValue );
            Float32 Get() const;

        private:
            Float32 _value;
        };

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
    } // namespace math
} // namespace ost