// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include <concepts>
#include <type_traits>

// ------------------------------------------------------------

template<typename T> concept EnumType = std::is_enum<T>::value;

template<EnumType T>
struct TIsEnumFlag : std::false_type {};

template<typename T> concept EnumFlagType = TIsEnumFlag<T>::value && EnumType<T>;

// ------------------------------------------------------------

template<EnumFlagType T>
T operator|(T a, T b)
{
	return static_cast<T>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

template<EnumFlagType T>
T operator&(T a, T b)
{
	return static_cast<T>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

template<EnumFlagType T>
T operator~(T e)
{
	return static_cast<T>(~static_cast<unsigned int>(e));
}

template<EnumFlagType T>
struct TFlags
{
	TFlags() = default;

	TFlags(T value)
		: Value(value)
	{
	}

	bool HasFlags(T f) const
	{
		return static_cast<unsigned>(Value & f) != 0;
	}

	void UnsetFlags(T f)
	{
		Value = Value & ~f;
	}

	TFlags& operator=(T e)
	{
		Value = e;
	}

	TFlags& operator=(const TFlags&) = default;

	T Value;
};


#define MAKE_ENUM_FLAG( E ) template<> struct TIsEnumFlag<E> : std::true_type {}

// ------------------------------------------------------------