#pragma once
#include <OstEngine/Types.h>
#include <OstEngine/Utility/IDType.h>
#include <OstEngine/Utility/SparseList.h>

namespace ost
{
    template<typename T>
    struct TIDIndexableGhostType;

	template< typename T >
    class TIDIndexableList
    {
        using IDType = TIDType<Uint64, TIDIndexableGhostType<T>>;

        TIDType PushAndGenerateID()
        {
            
        }

        T& operator[](const IDType& aID)
        {
            _container[aID.Get()];
        }

    private:
        TSparseList<T> _container;
    };
}