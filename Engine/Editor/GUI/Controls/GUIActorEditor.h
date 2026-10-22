// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

#include <Engine/World/IComponentFactory.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneEditorContext;
    class PropertyEditorDrawer;
    class Actor;

    class GUIActorEditor : public GUIControl
    {
    public:
        GUIActorEditor(SceneEditorContext& sceneEditCtx);

        void Display() override;

    private:
        void DisplayActorInfo(Actor& target);
        void DisplayActorComponents(Actor& target);
        bool DisplayComponentSelectPopup(Actor& target, TypeID& selectedID);

        void NewTargetActor();

        SceneEditorContext& _sceneEditorCtx;
        IComponentFactory& _componentFactory;
        PropertyEditorDrawer& _propertyDrawer;

        List<ComponentTypeInfo> _allComponentTypes;

        Actor* _cachedTarget;
        Vector3f _cachedEulers;
        std::string _cachedName;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------