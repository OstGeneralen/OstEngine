// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/EditorCommand.h"

#include <Container/Deque.h>
#include <Container/Queue.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class EditorCommandQueue
    {
    public:
        template <typename T>
        void PushCommand(UniquePtr<T>&& cmd)
        {
            _pendingCommands.Push(std::move(cmd));
        }

        void Execute(EditorContext& context);

    private:
        Queue<UniquePtr<EditorCommand>> _pendingCommands;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------