#pragma once
#include <limits>
#include <compare>

namespace ost
{
    template <typename TValue, typename TGhost>
    struct TIDType
    {
        TIDType() = default;
        explicit TIDType( const TIDType& ) = default;
        explicit TIDType(TValue aValue)
            : _idValue{ aValue }
        {
        }

        TIDType& operator=( const TIDType& ) = default;

        bool Valid() const
        {
            return _idValue != Invalid_v;
        }

        operator bool() const
        {
            return _idValue != Invalid_v;
        }

        TValue Get() const
        {
            return _idValue;
        }

        void Set(const TValue aValue)
        {
            _idValue = aValue;
        }

        bool operator==( const TIDType& ) const = default;
        auto operator<=>( const TIDType& ) const = default;
    private:
        constexpr static TValue Invalid_v = std::numeric_limits<TValue>::max;
        TValue _idValue = Invalid_v;
    };
}