// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Utility/Assert.h"

#include <OstTypes.h>
#include <queue>

// ------------------------------------------------------------
// ost::Queue<T>
// ------------------------------------------------------------
// Genuinely just a wrapper around the std queue :)
// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    class Queue
    {
    public:
        Queue() = default;
        Queue(const Queue&) = default;
        Queue(Queue&&) noexcept = default;
        ~Queue() = default;

        Queue& operator=(const Queue&) = default;
        Queue& operator=(Queue&&) noexcept = default;

        void Push(const T& t)
        {
            _queue.push(t);
        }
        void Push(T&& t)
        {
            _queue.push(std::move(t));
        }

        T* Peek()
        {
            if (IsEmpty())
            {
                return nullptr;
            }
            return &_queue.front();
        }
        const T* Peek() const
        {
            if (IsEmpty())
            {
                return nullptr;
            }
            return &_queue.front();
        }

        T Pop()
        {
            OST_ASSERT(!IsEmpty(), "May not pop from empty queue. Use TryPop instead?");
            T tmp = std::move(_queue.front());
            _queue.pop();
            return tmp;
        }
        bool TryPop(T& outPopped)
        {
            if (IsEmpty())
            {
                return false;
            }
            outPopped = std::move(_queue.front());
            _queue.pop();
            return true;
        }

        SizeType GetSize() const
        {
            return _queue.size();
        }

        bool IsEmpty() const
        {
            return _queue.empty();
        }

    private:
        std::queue<T> _queue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------