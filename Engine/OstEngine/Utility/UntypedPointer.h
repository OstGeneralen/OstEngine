#pragma once
#include <concepts>
#include <type_traits>

// ------------------------------------------------------------

namespace ost
{
    struct SUntypedPtr
    {
        SUntypedPtr()
            : _ptr{ nullptr }
        {
        }

        template<typename T>
        SUntypedPtr(T* aPtr)
            : _ptr{ static_cast<void*>(aPtr) }
        {
        }

        template<>
        SUntypedPtr(void* aPtr)
            : _ptr{aPtr}
        {
        }

        SUntypedPtr( const SUntypedPtr& aOther )
        {
            *this = aOther;
        }

        SUntypedPtr( SUntypedPtr&& aOther ) noexcept
        {
            *this = std::move( aOther );
        }

        template<typename T>
        SUntypedPtr& operator=(T* aPtr)
        {
            _ptr = static_cast<void*>( aPtr );
            return *this;
        }

        template<>
        SUntypedPtr& operator=(void* aPtr)
        {
            _ptr = aPtr;
            return *this;
        }

        SUntypedPtr& operator=( const SUntypedPtr& aRhs )
        {
            _ptr = aRhs._ptr;
        }

        SUntypedPtr& operator=( SUntypedPtr&& aRhs ) noexcept
        {
            _ptr = aRhs._ptr;
            aRhs._ptr = nullptr;
            return *this;
        }

        operator bool() const
        {
            return _ptr != nullptr;
        }

        template <typename T>
        T* Get()
        {
            return static_cast<T*>( _ptr );
        }

        template <typename T>
        const T* Get() const
        {
            return static_cast<const T*>( _ptr );
        }

    private:
        void* _ptr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------