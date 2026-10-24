// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"
#include "GUI/IEditorGUI.h"
#include "System/EditorCommand.h"

#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{

    class OpenWindowEditorCommand : public EditorCommand
    {
    public:
        template <typename T>
        static UniquePtr<OpenWindowEditorCommand> ForWindowType()
        {
            return Ptr::NewUnique<OpenWindowEditorCommand>(TypeID::Get<T>());
        }

        OpenWindowEditorCommand(TypeID type)
            : _windowType{type}
        {
        }

        void Execute(EditorContext& context) override
        {
            if (auto gui = context.serviceLocator.Get<IEditorGUI>())
            {
                gui->OpenWindow(_windowType);
            }
        }

    private:
        TypeID _windowType;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------