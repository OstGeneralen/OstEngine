#pragma once
#include <OstEngine/Types.h>


namespace ost
{
    struct SColorFlt32
    {
        Float32 R;
        Float32 G;
        Float32 B;
        Float32 A;
    };

	struct SColor
	{
        Uint8 R;
        Uint8 G;
        Uint8 B;
        Uint8 A;

        SColor();
        SColor( const Uint32 aHex );
        SColor( float aR, float aG, float aB, float aA );
        SColor( Uint8 aR, Uint8 aG, Uint8 aB, Uint8 aA );
        
        SColor( const SColor& ) = default;
        SColor& operator=( const SColor& ) = default;

        SColor& operator=( const Uint32 aHex );


        SColorFlt32 ToFlt32Color() const;

    };

    namespace Color
    {
        const static SColor White = 0xFFFFFFFF;
        const static SColor Black = 0x000000FF;
        const static SColor Red = 0xFF0000FF;
        const static SColor Green = 0x00FF00FF;
        const static SColor Blue = 0x0000FFFF;
    }
}