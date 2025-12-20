#pragma once
#include <OstEngine/Types.h>

namespace ost
{
    struct SColor;

    struct SColorFlt32
    {
        Float32 R;
        Float32 G;
        Float32 B;
        Float32 A;

        SColorFlt32();
        SColorFlt32( float aR, float aG, float aB, float aA = 1.0f );
        SColorFlt32( const SColor& aColor );
        SColorFlt32( const SColorFlt32& ) = default;

        SColorFlt32& operator=( const SColorFlt32& ) = default;
        SColorFlt32& operator=( const SColor& aColor );
    };

	struct SColor
	{
        Uint8 R;
        Uint8 G;
        Uint8 B;
        Uint8 A;

        SColor();
        SColor( const Uint32 aHex );
        SColor( Uint8 aR, Uint8 aG, Uint8 aB, Uint8 aA = 255u );
        SColor( const SColorFlt32& aFltColor );
        
        SColor( const SColor& ) = default;
        SColor& operator=( const SColor& ) = default;
        SColor& operator=( const Uint32 aHex );
        SColor& operator=( const SColorFlt32& aFltColor );
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