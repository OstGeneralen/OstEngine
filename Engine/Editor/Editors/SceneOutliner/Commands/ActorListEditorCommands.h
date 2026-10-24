// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"
#include "System/EditorCommand.h"

#include <OstTypes.h>

#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

// ------------------------------------------------------------

namespace ost
{
    class AddNewActorEditorCommand : public EditorCommand
    {
    public:
        void Execute(EditorContext& context) override
        {
            context.sceneContext.GetScenePtr()->CreateActor();
        }
    };

    class DeleteActorEditorCommand : public EditorCommand
    {
    public:
        DeleteActorEditorCommand(SizeType index)
            : _index{index}
        {
        }

        void Execute(EditorContext& context) override
        {
            context.sceneContext.GetScenePtr()->DestoryActor(context.sceneContext.GetActorPtr(_index));
        }

    private:
        SizeType _index;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------