// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIPanel.h"

#include <Math/Vector3.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ActorComponent;

    class PropertyEditorGUIPanel : public GUIPanel
    {
    public:
        void DrawGUI(EditorContext& context) override;

    private:
        ImGuiChildFlags GetDrawFlags() const override;

        void DrawComponentGui(EditorContext& context, TypeID componentType, const char* componentName, ActorComponent* pComponent);

        Actor* _pTarget = nullptr;
        Vector3f _position;
        Vector3f _rotation;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------