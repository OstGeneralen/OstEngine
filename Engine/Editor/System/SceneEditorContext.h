// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Utility/Delegate.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;
    class Actor;

    class SceneEditorContext
    {
    public:
        Delegate<Actor*> targetActorChanged;

        bool HasTargetActor() const;
        Actor* GetTargetActor();
        void SetTargetActor( Actor* pActor );

    private:
        Scene* _pEditedScene = nullptr;
        Actor* _pTargetActor = nullptr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------