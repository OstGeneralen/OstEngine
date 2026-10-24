// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"
#include "System/EditorCommand.h"

#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class AddComponentEditorCommand : public EditorCommand
    {
    public:
        AddComponentEditorCommand(TypeID componentType)
            : _componentType{componentType}
        {
        }

        void Execute(EditorContext& context) override
        {
            context.sceneContext.AddComponentToSelectedActor(_componentType);
        }

    private:
        TypeID _componentType;
    };

    class RemoveComponentEditorCommand : public EditorCommand
    {
    public:
        RemoveComponentEditorCommand(TypeID componentType)
        : _componentType{componentType}
        {
        }

        void Execute(EditorContext& context) override
        {
            context.sceneContext.RemoveComponentFromSelectedActor(_componentType);
        }

    private:
        TypeID _componentType;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------