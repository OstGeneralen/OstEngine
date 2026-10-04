#pragma once
#include <limits>

// ----------------------------------------------------------------------

using Int8 = signed char;
using Uint8 = unsigned char;
using Int16 = signed short;
using Uint16 = unsigned short;
using Int32 = signed int;
using Uint32 = unsigned int;
using Int64 = signed long long;
using Uint64 = unsigned long long;

using Float32 = float;
using Float64 = double;

// ----------------------------------------------------------------------

using SizeType = Uint64;
constexpr static SizeType SizeNone = -1;

// ----------------------------------------------------------------------

// Assert correct size
static_assert(sizeof(Int8) == 1 && sizeof(Uint8) == 1);
static_assert(sizeof(Int16) == 2 && sizeof(Uint16) == 2);
static_assert(sizeof(Int32) == 4 && sizeof(Uint32) == 4);
static_assert(sizeof(Int64) == 8 && sizeof(Uint64) == 8);
static_assert(sizeof(Float32) == 4);
static_assert(sizeof(Float64) == 8);

// ----------------------------------------------------------------------