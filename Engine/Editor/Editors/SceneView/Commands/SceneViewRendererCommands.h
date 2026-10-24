// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/EditorCommand.h"

#include <GraphicsEngine/Rendering/IRenderer.h>

// ------------------------------------------------------------

namespace ost
{
    class ResizeSceneViewEditorCommand : public EditorCommand
    {
    public:
        ResizeSceneViewEditorCommand()
        {
        }

        void Execute(EditorContext& context) override
        {
            context.sceneViewContext.ApplyOutputSizeToRenderer();
        }

    private:
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------