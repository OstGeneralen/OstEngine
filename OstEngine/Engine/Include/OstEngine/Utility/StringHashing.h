// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <string_view>

namespace ost
{
	namespace string_hash
	{
		constexpr static uint64 HashString_32(const std::string_view str)
		{
			uint32 hash = 0x811C9DC5;
			constexpr uint32 fnvPrime = 0x01000193;
			for (char c : str)
			{
				hash ^= static_cast<uint32>(c);
				hash *= fnvPrime;
			}
			return hash;
		}

		constexpr static uint64 HashString_64(const std::string_view str)
		{
			uint64 hash = 0xCBF29CE484222325;
			constexpr uint64 fnvPrime = 0x00000100000001B3;
			for (char c : str)
			{
				hash ^= static_cast<uint64>(c);
				hash *= fnvPrime;
			}
			return hash;
		}
	}
}