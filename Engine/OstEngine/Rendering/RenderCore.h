#pragma once
#include <OstEngine/Types.h>

template<Uint32 T>
struct PadBytes
{
	template<Uint32 TMod16>
	struct Internal
	{
        constexpr static Uint32 Num = 16 - TMod16;
	};

	template<>
	struct Internal<0>
	{
        constexpr static Uint32 Num = 0;
	};


    constexpr static Uint32 Num = Internal<T % 16>::Num;
};

template<typename T>
struct PadType
{
    constexpr static Uint32 PaddingBytes = PadBytes<sizeof( T )>::Num;
};

// ------------------------------------------------------------
// CBUFFER_DATA
// Macro that creates a variable DataType Name AND also pads
// to align the next element to be aligned at 16
// ------------------------------------------------------------
#define CBUFFER_DATA( DataType, Name )                                                                          \
    DataType Name;                                                                                              \
    const Byte PADDING_##Name[PadType<DataType>::PaddingBytes];

#define CBUFFER_STRUCTURE __declspec( align(16) )
