// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <compare>

// ------------------------------------------------------------

namespace ost
{
	struct SStableIndex
	{
		SStableIndex() = default;
		constexpr SStableIndex(uint64 stableIDValue) : _idValue{ stableIDValue } {}
		SStableIndex(const SStableIndex&) = default;
		SStableIndex(SStableIndex&&) noexcept = default;

		constexpr bool IsValid() const { return _idValue != STABLE_ID_INVALID; }
		void Invalidate() { _idValue = STABLE_ID_INVALID; }

		SStableIndex& operator=(const SStableIndex&) = default;

		bool operator==(const SStableIndex&) const = default;
		auto operator<=>(const SStableIndex&) const = default;

		constexpr uint64 Get() const { return _idValue; }
	private:
		constexpr static uint64 STABLE_ID_INVALID = 0xFFFFFFFFFFFFFFFFu;
		uint64 _idValue{STABLE_ID_INVALID};
	};
}

// ------------------------------------------------------------

namespace std
{
	template<>
	struct hash<ost::SStableIndex>
	{
		std::size_t operator()(const ost::SStableIndex& id) const noexcept
		{
			return id.Get();
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------