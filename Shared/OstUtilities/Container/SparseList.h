// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"
#include "Container/Queue.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    class SparseList
    {
    public:
        struct SparseSlotPair
        {
            SparseSlotPair(T& e, SizeType idx)
                : index{idx}
                , element{e}

            {
            }

            SparseSlotPair(const SparseSlotPair&) = default;

            SizeType index;
            T& element;
        };

    public:
        SparseList() = default;
        SparseList(const SparseList&) = default;
        SparseList(SparseList&&) noexcept = default;
        ~SparseList() = default;

        SparseList& operator=(const SparseList&) = default;
        SparseList& operator=(SparseList&&) noexcept = default;

        SparseSlotPair Add(const T& t)
        {
            const SizeType index = GenerateInsertIndex();
            if (index == _elements.GetSize())
            {
                return {_elements.Add(t), index};
            }
            T& element = _elements[index];
            element = t;
            return {element, index};
        }
        SparseSlotPair Add(T&& t)
        {
            const SizeType index = GenerateInsertIndex();
            if (index == _elements.GetSize())
            {
                return {_elements.Add(std::move(t)), index};
            }
            T& element = _elements[index];
            element = std::move(t);
            return {element, index};
        }

        void Remove(SizeType index)
        {
            // Default the element at this index to release any resources it owns
            _elements[index] = T{};
            _openIndexes.Push(index);
        }

        T& operator[](SizeType idx)
        {
            return _elements[idx];
        }
        const T& operator[](SizeType idx) const
        {
            return _elements[idx];
        }

    private:
        SizeType GenerateInsertIndex()
        {
            SizeType index = 0;
            if (_openIndexes.TryPop(index))
            {
                return index;
            }
            return _elements.GetSize();
        }

        List<T> _elements;
        Queue<SizeType> _openIndexes;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------