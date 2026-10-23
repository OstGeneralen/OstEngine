// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorCommandQueue.h"

using namespace ost;

// ------------------------------------------------------------

void ost::EditorCommandQueue::PushCommand(UniquePtr<EditorCommand>&& cmd)
{
    _pendingCommands.Push(std::move(cmd));
}

void EditorCommandQueue::Execute(EditorContext& context)
{
    while (!_pendingCommands.IsEmpty())
    {
        auto cmd = _pendingCommands.Pop();
        cmd->Execute(context);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------