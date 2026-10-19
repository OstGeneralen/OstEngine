// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct ViewRect
    {
        Vector2f position;
        Vector2f size;
    };

    class View
    {
    public:
        virtual ~View() = default;
        virtual void Present(const ViewRect& viewRect) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------