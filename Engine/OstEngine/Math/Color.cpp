#include "Color.h"

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

ost::SColor::SColor( float aR, float aG, float aB, float aA )
    : R{ static_cast<Uint8>( 255.0f * aR ) } 
    , G{ static_cast<Uint8>( 255.0f * aG ) }
    , B{ static_cast<Uint8>( 255.0f * aB ) }
    , A{ static_cast<Uint8>( 255.0f * aA ) }
{
}

ost::SColor::SColor( Uint8 aR, Uint8 aG, Uint8 aB, Uint8 aA )
    : R{aR}
    , G{aG}
    , B{aB}
    , A{aA}
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

ost::SColorFlt32 ost::SColor::ToFlt32Color() const
{
    return { static_cast<float>( R ) / 255.0f, static_cast<float>( G ) / 255.0f, static_cast<float>( B ) / 255.0f,
             static_cast<float>( A ) / 255.0f };
}
