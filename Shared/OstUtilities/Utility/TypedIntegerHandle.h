// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <compare>
#include <concepts>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    concept UIntType = std::is_unsigned_v<T> && std::is_integral_v<T>;

    template <typename T, UIntType TInteger = Uint64, TInteger InvalidValue = static_cast<TInteger>(-1)>
    struct TypedIntegerHandle
    {
        TypedIntegerHandle() = default;
        constexpr TypedIntegerHandle(const TypedIntegerHandle&) = default;
        constexpr TypedIntegerHandle(TypedIntegerHandle&&) noexcept = default;
        constexpr TypedIntegerHandle(TInteger v)
            : _value{v}
        {
        }

        constexpr TypedIntegerHandle& operator=(const TypedIntegerHandle&) = default;
        constexpr TypedIntegerHandle& operator=(TypedIntegerHandle&&) noexcept = default;
        constexpr TypedIntegerHandle& operator=( TInteger v )
        {
            _value = v;
            return *this;
        }

        constexpr auto operator==(const TypedIntegerHandle& rhs) const
        {
            return _value == rhs._value;
        }

        constexpr auto operator<=>(const TypedIntegerHandle&) const = default;

        constexpr bool Valid() const
        {
            return _value != InvalidValue;
        }

        constexpr operator bool() const
        {
            return Valid();
        }

        explicit constexpr operator TInteger() const
        {
            return _value;
        }

    private:
        TInteger _value = InvalidValue;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------