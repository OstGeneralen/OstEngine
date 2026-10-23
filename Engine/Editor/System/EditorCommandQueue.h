// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/IEditorCommandQueue.h"
#include "System/EditorCommand.h"

#include <Container/Deque.h>
#include <Container/Queue.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class EditorCommandQueue : public IEditorCommandQueue
    {
    public:
        void PushCommand(UniquePtr<EditorCommand>&& cmd) override;
        void Execute(EditorContext& context);

    private:
        Queue<UniquePtr<EditorCommand>> _pendingCommands;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------