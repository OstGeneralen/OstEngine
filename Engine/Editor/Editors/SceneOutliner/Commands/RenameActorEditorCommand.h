// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"
#include "System/EditorCommand.h"

#include <OstTypes.h>

#include <Engine/World/Actor.h>

// ------------------------------------------------------------

namespace ost
{
    class RenameActorEditorCommand : public EditorCommand
    {
    public:
        RenameActorEditorCommand(SizeType actorIndex, std::string newName)
            : _index{actorIndex}
            , _name{newName}
        {
        }

        void Execute(EditorContext& context) override
        {
            context.sceneContext.GetActorPtr(_index)->SetName(_name);
        }

    private:
        SizeType _index;
        std::string _name;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------