// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Memory/Memory.h"

#include <OstTypes.h>
#include <new>

// ------------------------------------------------------------

namespace ost
{
    class Blob
    {
    public:
        Blob()
            : _pData{nullptr}
            , _size{SizeNone}
        {
        }
        Blob(const Blob& other)
            : _pData{operator new[](other._size)}
            , _size(other._size)
        {
            MemCopy(_pData, other._pData, _size);
        }
        Blob(Blob&& other) noexcept
            : _pData{other._pData}
            , _size{other._size}
        {
            other._pData = nullptr;
            other._size = SizeNone;
        }
        Blob(const void* pData, SizeType size)
            : _pData{operator new[](size)}
            , _size{size}
        {
            MemCopy(_pData, pData, size);
        }
        Blob(SizeType size)
            : _pData{operator new[](size)}
            , _size{size}
        {
        }
        ~Blob()
        {
            TryRelease();
        }

        Blob& operator=(const Blob& rhs)
        {
            TryRelease();

            _pData = operator new[](rhs._size);
            _size = rhs._size;

            MemCopy(_pData, rhs._pData, _size);

            return *this;
        }
        Blob& operator=(Blob&& rhs) noexcept
        {
            TryRelease();
            std::swap(_pData, rhs._pData);
            std::swap(_size, rhs._size);
            return *this;
        }

        const void* Data() const
        {
            return _pData;
        }
        SizeType Size() const
        {
            return _size;
        }

        void* DataWritable()
        {
            return _pData;
        }

        bool IsValid() const
        {
            return _pData != nullptr && _size != SizeNone;
        }

    private:
        void TryRelease()
        {
            if (_pData != nullptr)
            {
                operator delete[](_pData, _size);
                _pData = nullptr;
                _size = SizeNone;
            }
        }

        void* _pData;
        SizeType _size;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------