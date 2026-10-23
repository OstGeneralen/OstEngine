// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorCommand;

    class IEditorCommandQueue
    {
    public:
        virtual ~IEditorCommandQueue() = default;
        virtual void PushCommand(UniquePtr<EditorCommand>&& cmd) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------