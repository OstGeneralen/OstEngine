// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Utility/Assert.h"

#include <OstTypes.h>
#include <vector>

// ------------------------------------------------------------
// ost::List<T>
// ------------------------------------------------------------
// Genuinely just a wrapper around the std vector :)
// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    class List
    {
    public:
        List() = default;
        List(const List&) = default;
        List(List&&) noexcept = default;
        explicit List(SizeType size)
            : _vector(size)
        {
        }
        List(std::initializer_list<T> il)
            : _vector(il)
        {
        }
        ~List() = default;

        List& operator=(std::initializer_list<T> il)
        {
            _vector = il;
            return *this;
        }
        List& operator=(const List&) = default;
        List& operator=(List&&) noexcept = default;

        void Reserve(SizeType capacity)
        {
            _vector.reserve(capacity);
        }
        void Resize(SizeType size)
        {
            _vector.resize(size);
        }

        template <typename... TArgs>
        T& Emplace(TArgs&&... args)
        {
            return _vector.emplace_back(std::forward<TArgs>(args)...);
        }
        T& Add(const T& t)
        {
            _vector.push_back(t);
            return _vector.back();
        }
        T& Add(T&& t)
        {
            _vector.push_back(std::move(t));
            return _vector.back();
        }

        void Remove(SizeType index)
        {
            OST_ASSERT(index < GetSize(), "Must not be out of bounds");

            if (index < GetSize() - 1)
            {
                _vector[index] = std::move(_vector.back());
            }
            _vector.pop_back();
        }

        void Clear()
        {
            _vector.clear();
        }

        T* GetData()
        {
            return _vector.data();
        }
        const T* GetData() const
        {
            return _vector.data();
        }

        SizeType GetSize() const
        {
            return _vector.size();
        }
        SizeType GetCapacity() const
        {
            return _vector.capacity();
        }
        bool IsEmpty() const
        {
            return _vector.empty();
        }

        T& operator[](SizeType index)
        {
            return _vector[index];
        }
        const T& operator[](SizeType index) const
        {
            return _vector[index];
        }

        auto begin()
        {
            return _vector.begin();
        }
        auto end()
        {
            return _vector.end();
        }

        auto begin() const
        {
            return _vector.begin();
        }
        auto end() const
        {
            return _vector.end();
        }

        auto rbegin()
        {
            return _vector.rbegin();
        }
        auto rend()
        {
            return _vector.rend();
        }

        auto cbegin() const
        {
            return _vector.cbegin();
        }
        auto cend() const
        {
            return _vector.cend();
        }

        auto crbegin() const
        {
            return _vector.crbegin();
        }
        auto crend() const
        {
            return _vector.crend();
        }

    private:
        std::vector<T> _vector;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------