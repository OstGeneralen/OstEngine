// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/EditorCommandQueue.h"

#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext
    {
    public:
        EditorContext(ServiceLocator& services)
            : serviceLocator{services}
        {
        }

        ServiceLocator& serviceLocator;
        EditorCommandQueue commandQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------