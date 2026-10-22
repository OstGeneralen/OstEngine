// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Utility/Hash.h"

#include <compare>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class StringID
    {
    public:
        StringID()
            : _str{}
            , _hash{0}
        {
        }
        StringID(const std::string& str)
            : _str{str}
            , _hash{hash::fnv1a(_str)}
        {
        }
        StringID(const char* cStr)
            : _str{cStr}
            , _hash{hash::fnv1a(_str)}
        {
        }
        StringID(const StringID& strID) = default;

        StringID& operator=(const std::string& str)
        {
            _str = str;
            _hash = hash::fnv1a(_str);
            return *this;
        }
        StringID& operator=(const char* cStr)
        {
            _str = cStr;
            _hash = hash::fnv1a(_str);
            return *this;
        }
        StringID& operator=(const StringID& strID) = default;

        const std::string& GetString() const
        {
            return _str;
        }
        Uint64 GetHash() const noexcept
        {
            return _hash;
        }

        bool operator==(const StringID& rhs) const
        {
            return _hash == rhs._hash;
        }
        bool operator!=(const StringID& rhs) const
        {
            return _hash != rhs._hash;
        }
        auto operator<=>(const StringID& rhs) const noexcept
        {
            return _hash <=> rhs._hash;
        }

    private:
        std::string _str;
        Uint64 _hash;
    };
} // namespace ost

namespace std
{
    template <>
    struct hash<ost::StringID>
    {
        size_t operator()(const ost::StringID& sID) const noexcept
        {
            return sID.GetHash();
        }
    };
} // namespace std

static inline ost::StringID operator""_sid(const char* s)
{
    return ost::StringID{s};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------