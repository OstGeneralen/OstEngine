// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <concepts>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    class UniquePtr;

    namespace Ptr
    {
        template <typename T, typename... TArgs>
        inline UniquePtr<T> NewUnique(TArgs&&... ctorArgs)
        {
            return UniquePtr<T>(new T{std::forward<TArgs>(ctorArgs)...});
        }
    } // namespace Ptr

    template <typename T>
    class UniquePtr
    {
    public:
        template <typename T2>
        friend class UniquePtr;

        // Disallow copies
        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

    public:
        UniquePtr()
            : _raw{nullptr}
        {
        }
        UniquePtr(T* p)
            : _raw{p}
        {
        }
        UniquePtr(UniquePtr&& o) noexcept
            : _raw{o._raw}
        {
            o._raw = nullptr;
        }
        ~UniquePtr()
        {
            Reset();
        }

        template<typename T2>
        UniquePtr( UniquePtr<T2>&& o ) noexcept
            : _raw{o._raw}
        {
            o._raw = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& o) noexcept
        {
            Reset();
            _raw = o._raw;
            o._raw = nullptr;
            return *this;
        }
        UniquePtr& operator=(std::nullptr_t)
        {
            Reset();
            return *this;
        }

        template <typename T2>
        UniquePtr& operator=(UniquePtr<T2>&& o) noexcept
        {
            Reset();
            _raw = o._raw;
            o._raw = nullptr;
            return *this;
        }

        T* Get()
        {
            return _raw;
        }
        const T* Get() const
        {
            return _raw;
        }

        template <typename T2>
        T2* GetAs()
        {
            return reinterpret_cast<T2*>(_raw);
        }

        template <typename T2>
        const T2* GetAs() const
        {
            return reinterpret_cast<const T2*>(_raw);
        }

        void Reset()
        {
            if (_raw)
            {
                delete _raw;
                _raw = nullptr;
            }
        }

        bool IsValid() const
        {
            return _raw != nullptr;
        }

        T* operator->()
        {
            return _raw;
        }
        const T* operator->() const
        {
            return _raw;
        }

        T& operator*()
        {
            return *_raw;
        }
        const T& operator*() const
        {
            return *_raw;
        }

        operator bool() const
        {
            return _raw != nullptr;
        }

    private:
        T* _raw;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------