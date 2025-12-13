#pragma once

// ------------------------------------------------------------

#define SIZED_TYPEDEF( Name, Type, Bytes )                                                                             \
    using Name = Type;                                                                                                 \
    static_assert( sizeof( Name ) == Bytes );

// ------------------------------------------------------------

SIZED_TYPEDEF(Int8, signed char, 1)
SIZED_TYPEDEF(Uint8, unsigned char, 1 )
SIZED_TYPEDEF(Byte, unsigned char, 1)

SIZED_TYPEDEF(Int16, signed short, 2)
SIZED_TYPEDEF(Uint16, unsigned short, 2)

SIZED_TYPEDEF(Int32, signed int, 4)
SIZED_TYPEDEF(Uint32, unsigned int, 4)

SIZED_TYPEDEF(Int64, signed long long, 8)
SIZED_TYPEDEF(Uint64, unsigned long long, 8)

SIZED_TYPEDEF(Float32, float, 4)
SIZED_TYPEDEF(Float64, double, 8)

using CStyleString = char*;

// ------------------------------------------------------------
