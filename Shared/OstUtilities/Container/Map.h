// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <unordered_map>

// ------------------------------------------------------------
// ost::Map<TKey, T>
// ------------------------------------------------------------
// Just a wrapper around unordered_map
// ------------------------------------------------------------

namespace ost
{
    template <typename TKey, typename T>
    class Map
    {
    public:
        Map() = default;
        Map(const Map&) = default;
        Map(Map&&) noexcept = default;
        ~Map() = default;

        Map& operator=(const Map&) = default;
        Map& operator=(Map&&) = default;

        T& Insert(const TKey& key, const T& value)
        {
            return _map.insert({key, value}).first->second;
        }
        T& Insert(const TKey& key, T&& value)
        {
            return _map.insert({key, std::move(value)}).first->second;
        }

        void InsertOrOverwrite(const TKey& key, const T& value)
        {
            _map[key] = value;
        }
        void InsertOrOverwrite(const TKey& key, T&& value)
        {
            _map[key] = std::move(value);
        }

        void Clear()
        {
            _map.clear();
        }

        void Remove(const TKey& key)
        {
            _map.erase(key);
        }

        T* TryGetValue(const TKey& key)
        {
            auto it = _map.find(key);
            if (it == _map.end())
            {
                return nullptr;
            }
            return &(it->second);
        }
        const T* TryGetValue(const TKey& key) const
        {
            auto it = _map.find(key);
            if (it == _map.end())
            {
                return nullptr;
            }
            return &(it->second);
        }

        bool Contains(const TKey& key)
        {
            return _map.contains(key);
        }
        bool IsEmpty() const
        {
            return _map.empty();
        }

        // Intentionally different behaviour from std::unordered_map
        // Operator[] is a getter only, does not accidentally create new elements
        T& operator[](const TKey& key)
        {
            return _map.at(key);
        }
        const T& operator[](const TKey& key) const
        {
            return _map.at(key);
        }

        auto begin()
        {
            return _map.begin();
        }
        auto end()
        {
            return _map.end();
        }
        auto begin() const
        {
            return _map.begin();
        }
        auto end() const
        {
            return _map.end();
        }
        auto cbegin() const
        {
            return _map.cbegin();
        }
        auto cend() const
        {
            return _map.cend();
        }

    private:
        std::unordered_map<TKey, T> _map;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------