#pragma once
#include <OstEngine/Common/Math/Vectors.h>

// --------------------------------------------------

namespace ost
{
	union InputValue
	{
        InputValue( const bool& aB )
            : ButtonValue{ aB }
        {
        }

        InputValue( const float& aF )
            : Axis1DValue{ aF }
        {
        }

        InputValue( const Vector2f& aV )
            : Axis2DValue{aV}
        {
        }


        Vector2f Axis2DValue;
        float Axis1DValue;
        bool ButtonValue;
	};
}

// --------------------------------------------------
// --------------------------------------------------
// --------------------------------------------------