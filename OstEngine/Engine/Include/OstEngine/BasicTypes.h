// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once 
#include <concepts>
#include <type_traits>

// ------------------------------------------------------------

namespace ost
{
	// 8-bit
	using uint8		= unsigned char;
	using int8		= signed char;
	using byte		= uint8;

	// 16-bit
	using uint16	= unsigned short;
	using int16		= signed short;

	// 32-bit
	using uint32	= unsigned int;
	using int32		= signed int;
	using float32	= float;

	// 64-bit
	using uint64	= unsigned long long;
	using int64		= signed long long;
	using float64	= long double;

	template<typename T> concept UnsignedIntType	= std::is_same_v<T,  uint8> || std::is_same_v<T, uint16> || std::is_same_v<T, uint32> || std::is_same_v<T, uint64>;
	template<typename T> concept SignedIntType		= std::is_same_v<T, int8> || std::is_same_v<T, int16> || std::is_same_v<T, int32> || std::is_same_v<T, int64>;
	template<typename T> concept FloatingPointType	= std::is_same_v<T, float32> || std::is_same_v<T, float64>;
	template<typename T> concept IntType			= UnsignedIntType<T> || SignedIntType<T>;
	template<typename T> concept NumericType		= IntType<T> || FloatingPointType<T>;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------