// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Utility/Delegate.h>
#include "Engine/World/Actor.h"

// ------------------------------------------------------------

namespace ost
{
    class Scene;

    class SceneEditorContext
    {
    public:
        Delegate<> targetActorChanged;

        bool HasTargetActor() const;
        Actor* GetTargetActor();
        void SetTargetActor( Actor* pActor );

        List<ComponentData>& GetTargetActorComponentsInfo();

    private:
        Scene* _pEditedScene = nullptr;
        Actor* _pTargetActor = nullptr;
        List<ComponentData> _targetActorComponentData;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------