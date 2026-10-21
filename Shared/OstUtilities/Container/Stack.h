// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <stack>

// ------------------------------------------------------------

namespace ost
{
    template<typename T>
    class Stack
    {
    public:
        Stack() = default;
        Stack(const Stack&) = default;
        Stack(Stack&&) noexcept = default;
        ~Stack() = default;

        Stack& operator=(const Stack&) = default;
        Stack& operator=(Stack&&) noexcept = default;

        void Push(const T& t)
        {
            _stack.push(t);
        }
        void Push(T&& t)
        {
            _stack.push(std::move(t));
        }

        void Pop()
        {
            _stack.pop();
        }
        T PopAndGet()
        {
            T value = _stack.top();
            _stack.pop();
            return value;
        }

        T* Peek()
        {
            if (_stack.empty())
            {
                return nullptr;
            }
            return &_stack.top();
        }
        const T* Peek() const
        {
            if (_stack.empty())
            {
                return nullptr;
            }
            return &_stack.top();
        }

        T& Top()
        {
            return _stack.top();
        }
        const T& Top() const
        {
            return _stack.top();
        }

        bool IsEmpty() const
        {
            return _stack.empty();
        }

    private:
        std::stack<T> _stack;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------