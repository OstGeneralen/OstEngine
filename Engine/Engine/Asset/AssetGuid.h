// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <compare>
#include <random>
#include <tuple>

// ------------------------------------------------------------

namespace ost
{
    struct alignas(16) AssetGuid
    {
        friend struct std::hash<AssetGuid>;

        AssetGuid() = default;

        constexpr AssetGuid(Uint64 h, Uint64 l) noexcept
            : _high{h}
            , _low{l}
        {
        }

        constexpr bool operator==(const AssetGuid& rhs) const noexcept
        {
            return _high == rhs._high && _low == rhs._low;
        }

        constexpr bool operator!=(const AssetGuid& rhs) const noexcept
        {
            return !(*this == rhs);
        }

        constexpr auto operator<=>(const AssetGuid& rhs) const noexcept
        {
            return std::tie(_high, rhs._high) <=> std::tie(_low, rhs._low);
        }

        static AssetGuid Generate() noexcept
        {
            thread_local std::mt19937_64 rng{std::random_device{}()};
            return AssetGuid{rng(), rng()};
        }

        constexpr operator bool() const noexcept
        {
            return (_high != 0) && (_low != 0);
        }

    private:
        Uint64 _high = 0;
        Uint64 _low = 0;
    };
} // namespace ost

namespace std
{
    template <>
    struct hash<ost::AssetGuid>
    {
        size_t operator()(const ost::AssetGuid& guid) const noexcept
        {
            Uint64 x = guid._high ^ guid._low;
            x ^= x >> 30;
            x *= 0xBF58476D1CE4E5B9ULL;
            x ^= x >> 27;
            x *= 0x94D049BB133111EBULL;
            x ^= x >> 31;
            return static_cast<size_t>(x);
        }
    };

} // namespace std

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------