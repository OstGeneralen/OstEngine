#pragma once
#include <OstEngine/Types.h>

#include <deque>
#include <vector>
#include <algorithm>

namespace ost
{
    template <typename T>
    class TSparseList
    {
    public:
        TSparseList() = default;
        TSparseList( const TSparseList& ) = default;
        TSparseList( TSparseList&& ) noexcept = default;
        ~TSparseList() = default;

        void Clear()
        {
            _elements.clear();
            _freeIds.clear();
        }

        Uint64 FreeIndexCount() const
        {
            return _freeIds.size();
        }

        Uint64 Size() const
        {
            return _elements.size();
        }

        T& operator[](const Uint64 aIdx)
        {
            return _elements[aIdx];
        }

        const T& operator[](const Uint64 aIdx) const
        {
            return _elements[aIdx];
        }

        bool IsIndexValid(const Uint64 aIdx) const
        {
            // Early out if this index could just not be valid due to size
            if (aIdx > _elements.size())
            {
                return false;
            }

            // Make sure not in free indexes
            return std::find( _freeIds.begin(), _freeIds.end(), aIdx ) == _freeIds.end();
        }

        void Remove(const Uint64 aIndex)
        {
            _freeIds.push_back( aIndex );
        }

        T& Push( const T& aElem )
        {
            Uint64 createAt = _elements.size();
            if ( _freeIds.empty() == false )
            {
                createAt = _freeIds.front();
                _freeIds.pop_front();
                _elements[createAt] = aElem;
            }
            else
            {
                _elements.push_back( aElem );
            }
            return _elemets[createAt];
        }

        T& Push( T&& aElem )
        {
            Uint64 createAt = _elements.size();
            if ( _freeIds.empty() == false )
            {
                createAt = _freeIds.front();
                _freeIds.pop_front();
                _elements[createAt] = std::move( aElem );
            }
            else
            {
                _elements.push_back( std::move( aElem ) );
            }
            return _elements[createAt];
        }

        template <typename... TArgs>
        T& Emplace( TArgs&&... aArgs )
        {
            Uint64 createAt = _elements.size();
            if (_freeIds.empty() == false)
            {
                createAt = _freeIds.front();
                _freeIds.pop_front();
                _elements.emplace( _elements.begin() + createAt, aArgs... );
            }
            else
            {
                _elements.emplace_back( aArgs... );
            }
            return _elements[createAt];
        }

    private:
        std::vector<T> _elements;
        std::deque<Uint64> _freeIds;
    };
} // namespace ost
