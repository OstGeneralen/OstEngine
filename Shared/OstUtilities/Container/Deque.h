// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <deque>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    class Deque
    {
    public:
        Deque() = default;
        Deque(const Deque&) = default;
        Deque(Deque&&) noexcept = default;

        Deque& operator=(const Deque&) = default;
        Deque& operator=(Deque&&) noexcept = default;

        void PushBack(const T& t)
        {
            _deque.push_back(t);
        }

        void PushBack(T&& t)
        {
            _deque.push_back(std::move(t));
        }

        void PushFront(const T& t)
        {
            _deque.push_front(t);
        }

        void PushFront(T&& t)
        {
            _deque.push_front(std::move(t));
        }

        void PopBack()
        {
            _deque.pop_back();
        }

        void PopFront()
        {
            _deque.pop_front();
        }

        const T& PeekFront() const
        {
            return _deque.front();
        }

        const T& PeekBack() const
        {
            return _deque.back();
        }

        SizeType GetSize() const
        {
            return _deque.size();
        }

        bool IsEmpty() const
        {
            return _deque.empty();
        }

    private:
        std::deque<T> _deque;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------