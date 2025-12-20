#pragma once
#include <concepts>
#include <type_traits>

// ------------------------------------------------------------

template<typename T>
concept PointerType = std::is_pointer_v<T>;

template<typename T>
concept NonPointerType = !std::is_pointer_v<T>;

// ------------------------------------------------------------

namespace ost
{
    struct SUntypedPtr
    {
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

        SUntypedPtr();
        SUntypedPtr( const SUntypedPtr& aOther );
        SUntypedPtr( SUntypedPtr&& aOther ) noexcept;
        SUntypedPtr& operator=( const SUntypedPtr& aRhs );
        SUntypedPtr& operator=( SUntypedPtr&& aRhs ) noexcept;
        operator bool() const;

        template<NonPointerType T>
        SUntypedPtr& operator=(T* aPtr)
        {
            _ptr = static_cast<void*>( aPtr );
            return *this;
        }

        template<PointerType T>
        SUntypedPtr& operator=(T aPtr)
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

        template <NonPointerType T>
        T* Get()
        {
            return static_cast<T*>( _ptr );
        }

        template <NonPointerType T>
        const T* Get() const
        {
            return static_cast<const T*>( _ptr );
        }

        template<PointerType T>
        T Get()
        {
            return static_cast<T>( _ptr );
        }

        template <PointerType T>
        const T Get() const
        {
            return static_cast<const T>( _ptr );
        }
    private:
        void* _ptr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------