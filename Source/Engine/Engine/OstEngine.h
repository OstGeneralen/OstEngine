// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsEngine;

    class OstEngine;
    extern OstEngine* pEngine;

    class OstEngine
    {
    public:
        OstEngine();
        ~OstEngine();

        GraphicsEngine& GetGraphicsEngine();
        const GraphicsEngine& GetGraphicsEngine() const;

    private:
        UniquePtr<GraphicsEngine> _graphicsEngine;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------