#include "OstEngine/Math/Color.h"

// ------------------------------------------------------------
// Flt32 Color
// ------------------------------------------------------------

ost::SColorFlt32::SColorFlt32()
    : R{ 0.0f }
    , G{ 0.0f }
    , B{ 0.0f }
    , A{ 1.0f }
{
}

ost::SColorFlt32::SColorFlt32( float aR, float aG, float aB, float aA )
    : R{ aR }
    , G( aG )
    , B{ aB }
    , A{ aA }
{
}

ost::SColorFlt32::SColorFlt32( const SColor& aColor )
    : R{ static_cast<float>( aColor.R ) / 255.0f }
    , G{ static_cast<float>( aColor.G ) / 255.0f }
    , B{ static_cast<float>( aColor.B ) / 255.0f }
    , A{ static_cast<float>( aColor.A ) / 255.0f }
{
}

ost::SColorFlt32& ost::SColorFlt32::operator=( const SColor& aColor )
{
    R = static_cast<float>( aColor.R ) / 255.0f;
    G = static_cast<float>( aColor.G ) / 255.0f;
    B = static_cast<float>( aColor.B ) / 255.0f;
    A = static_cast<float>( aColor.A ) / 255.0f;
    return *this;
}

// ------------------------------------------------------------
// Standard SColor (Uint8)
// ------------------------------------------------------------

ost::SColor::SColor()
    : R{ 0 }
    , G{ 0 }
    , B{ 0 }
    , A{ 255 }

{
}

ost::SColor::SColor( const Uint32 aHex )
    : SColor()
{
    *this = aHex;
}

ost::SColor::SColor( Uint8 aR, Uint8 aG, Uint8 aB, Uint8 aA )
    : R{ aR }
    , G{ aG }
    , B{ aB }
    , A{ aA }
{
}

ost::SColor::SColor( const SColorFlt32& aFltColor )
    : SColor( static_cast<Uint8>( aFltColor.R * 255.0f ), static_cast<Uint8>( aFltColor.G * 255.0f ),
              static_cast<Uint8>( aFltColor.B * 255.0f ), static_cast<Uint8>( aFltColor.A * 255.0f ) )
{
}

ost::SColor& ost::SColor::operator=( const Uint32 aHex )
{
    R = static_cast<Uint8>( ( aHex & 0xFF000000 ) >> 24 );
    G = static_cast<Uint8>( ( aHex & 0x00FF0000 ) >> 16 );
    B = static_cast<Uint8>( ( aHex & 0x0000FF00 ) >> 8 );
    A = static_cast<Uint8>( ( aHex & 0x000000FF ) );
    return *this;
}

ost::SColor& ost::SColor::operator=( const SColorFlt32& aFltColor )
{
    R = static_cast<Uint8>( 255.0f * aFltColor.R );
    G = static_cast<Uint8>( 255.0f * aFltColor.G );
    B = static_cast<Uint8>( 255.0f * aFltColor.B );
    A = static_cast<Uint8>( 255.0f * aFltColor.A );
    return *this;
}