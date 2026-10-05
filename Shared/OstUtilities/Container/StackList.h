// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Utility/Assert.h"

#include <OstTypes.h>
#include <new>

#include <Memory/Memory.h>

// ------------------------------------------------------------
// ost::StackList<T, TCapacity>
// ------------------------------------------------------------
// A vector-like structure that sits in stack memory
// This is really just a "fancy array"
//
// ## OPERATION COMPLEXITY ##
// | OP      | Complexity   |
// |---------|--------------|
// | Add     | O(1)         |
// | Remove  | O(1)         |
// | Index   | O(1)         |
// ------------------------------------------------------------

namespace ost
{
    template <typename T, SizeType TCapacity>
    class StackList
    {
    public:
        StackList()
            : _storage{}
            , _size{0}
        {
        }
        StackList(const StackList& o)
            : _storage{}
            , _size{0}
        {
            if constexpr (std::is_trivially_copyable_v<T>)
            {
                MemCopy(_storage, o._storage, o._size * sizeof(T));
                _size = o._size;
            }
            else
            {
                for (SizeType i = 0; i < o._size; ++i)
                {
                    Add(o.GetElement(i));
                }
            }
        }
        StackList(StackList&& o) noexcept
            : _storage{}
            , _size{0}
        {
            if constexpr (std::is_trivially_copyable_v<T>)
            {
                MemCopy(_storage, o._storage, sizeof(T) * o._size);
                _size = o._size;
            }
            else
            {
                for (SizeType i = 0; i < o._size; ++i)
                {
                    Emplace(std::move(o.GetElement(i)));
                }
            }

            o.Clear();
        }
        ~StackList()
        {
            Clear();
        }

        template <typename... TArgs>
        T& Emplace(TArgs&&... args)
        {
            OST_ASSERT(_size < TCapacity, "Must not be full");

            new (GetAddress(_size)) T(std::forward<TArgs>(args)...);
            _size++;
            return GetElement(_size - 1);
        }
        T& Add(const T& t)
        {
            return Emplace(t);
        }
        T& Add(T&& t)
        {
            return Emplace(std::move(t));
        }

        void Remove(SizeType index)
        {
            OST_ASSERT(!IsEmpty(), "Must not be empty");
            OST_ASSERT(index < _size, "Must not be out of bounds");

            if (index < _size - 1)
            {
                // Move the last element to the deleted space
                GetElement(index) = std::move(GetElement(_size - 1));
            }

            _size--;

            if constexpr (std::is_trivially_destructible_v<T> == false)
            {
                GetElement(_size).~T();
            }
        }

        void Clear()
        {
            if constexpr (std::is_trivially_destructible_v<T> == false)
            {
                for (SizeType i = 0; i < _size; ++i)
                {
                    GetElement(i).~T();
                }
            }
            _size = 0;
        }

        SizeType GetSize() const
        {
            return _size;
        }
        SizeType GetCapacity() const
        {
            return TCapacity;
        }

        bool IsEmpty() const
        {
            return _size == 0;
        }

        StackList& operator=(const StackList& o)
        {
            if (this == &o)
            {
                return *this;
            }

            Clear();

            if constexpr (std::is_trivially_copyable_v<T>)
            {
                MemCopy(_storage, o._storage, o._size * sizeof(T));
                _size = o._size;
            }
            else
            {
                for (SizeType i = 0; i < o._size; ++i)
                {
                    Emplace(o.GetElement(i));
                }
            }

            return *this;
        }
        StackList& operator=(StackList&& o) noexcept
        {
            if (this == &o)
            {
                return *this;
            }

            Clear();

            if constexpr (std::is_trivially_copyable_v<T>)
            {
                MemCopy(_storage, o._storage, o._size * sizeof(T));
                _size = o._size;
            }
            else
            {
                for (SizeType i = 0; i < o._size; ++i)
                {
                    Emplace(std::move(o.GetElement(i)));
                }
            }
            o.Clear();

            return *this;
        }

        T& operator[](SizeType index)
        {
            OST_ASSERT(index < _size, "Must not be out of bounds");
            return GetElement(index);
        }
        const T& operator[](SizeType index) const
        {
            OST_ASSERT(index < _size, "Must not be out of bounds");
            return GetElement(index);
        }

        T* begin()
        {
            return GetAddress(0);
        }
        T* end()
        {
            return GetAddress(_size);
        }

        const T* begin() const
        {
            return GetAddress(0);
        }
        const T* end() const
        {
            return GetAddress(_size);
        }

    private:
        T* GetAddress(SizeType index)
        {
            return reinterpret_cast<T*>(_storage) + index;
        }
        const T* GetAddress(SizeType index) const
        {
            return reinterpret_cast<const T*>(_storage) + index;
        }

        T& GetElement(SizeType index)
        {
            return *GetAddress(index);
        }
        const T& GetElement(SizeType index) const
        {
            return *GetAddress(index);
        }

    private:
        alignas(alignof(T)) Uint8 _storage[TCapacity * sizeof(T)];
        SizeType _size;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------