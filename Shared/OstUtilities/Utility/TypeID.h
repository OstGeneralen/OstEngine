// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <compare>
#include <source_location>
#include <string_view>
#include <type_traits>

// ------------------------------------------------------------

namespace ost
{
    namespace hash
    {
        constexpr inline Uint64 fnv1a(std::string_view s)
        {
            Uint64 hash = 14695981039346656037ULL;
            for (char c : s)
            {
                hash ^= static_cast<uint64_t>(c);
                hash *= 1099511628211ULL;
            }
            return hash;
        }
    } // namespace hash

    struct TypeID
    {
        template <typename T>
        static constexpr inline TypeID Get()
        {
            return TypeID{hash::fnv1a(std::source_location::current().function_name())};
        }

        constexpr inline TypeID(SizeType id)
            : _id{id}
        {
        }

        constexpr inline TypeID(const TypeID& t)
            : _id{t._id}
        {
        }

        constexpr inline TypeID& operator=(const TypeID& t)
        {
            _id = t._id;
            return *this;
        }

        constexpr inline auto operator<=>(const TypeID& o) const
        {
            return _id <=> o._id;
        }

        constexpr inline operator SizeType() const
        {
            return _id;
        }

    private:
        SizeType _id;
    };

} // namespace ost

// ------------------------------------------------------------

namespace std
{
    template <>
    struct hash<ost::TypeID>
    {
        size_t operator()(const ost::TypeID& tid) const noexcept
        {
            return static_cast<size_t>(tid);
        }
    };
} // namespace std

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------