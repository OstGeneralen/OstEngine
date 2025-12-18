#include "OstEngine/Utility/UntypedPointer.h"

// ------------------------------------------------------------

ost::SUntypedPtr::SUntypedPtr()
    : _ptr{ nullptr }
{
}

ost::SUntypedPtr::SUntypedPtr( const SUntypedPtr& aOther )
    : _ptr{aOther._ptr}
{
}

ost::SUntypedPtr::SUntypedPtr( SUntypedPtr&& aOther ) noexcept
    : _ptr{aOther._ptr}
{
    aOther._ptr = nullptr;
}

ost::SUntypedPtr& ost::SUntypedPtr::operator=( const SUntypedPtr& aRhs )
{
    _ptr = aRhs._ptr;
    return *this;
}

ost::SUntypedPtr& ost::SUntypedPtr::operator=( SUntypedPtr&& aRhs ) noexcept
{
    _ptr = aRhs._ptr;
    aRhs._ptr = nullptr;
    return *this;
}

ost::SUntypedPtr::operator bool() const
{
    return _ptr != nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------