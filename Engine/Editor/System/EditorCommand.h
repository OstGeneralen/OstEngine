// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class EditorCommand
    {
    public:
        virtual ~EditorCommand() = default;

        virtual void Execute(EditorContext& context) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------