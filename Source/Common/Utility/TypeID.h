// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <compare>
#include <type_traits>

// ------------------------------------------------------------

namespace ost
{
    struct TypeID
    {
        template <typename T>
        static inline TypeID Get()
        {
            return TypeID{typeid(T).hash_code()};
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
        size_t operator()(const ost::TypeID& tid) noexcept
        {
            return static_cast<size_t>(tid);
        }
    };
} // namespace std

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------