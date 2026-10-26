// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Editors/AssetView/AssetTypes.h"
#include "GUI/Controls/PropertyEditors/PropertyEditor.h"
#include "GUI/OstGui.h"

#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class ModelHandlePropertyEditor : public PropertyTypeEditor<HModel>
    {
        void Display(const char* name, HModel& data) override
        {
            OstGui::PushStyleColor(ImGuiCol_ChildBg, {1, 1, 1, 0.1f});
            OstGui::BeginChild("ModelEntry", {0, 0}, ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders);

            const Vector2f dropZonePos = OstGui::GetCursorPos();

            OstGui::Text("%i", static_cast<SizeType>(data));

            const Vector2f dropZoneSize = {0, OstGui::GetItemRectSize().y};

            OstGui::SetCursorPos(dropZonePos);
            OstGui::Selectable("##DropZone", false, ImGuiSelectableFlags_AllowOverlap, dropZoneSize);
            if (OstGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = OstGui::AcceptDragDropPayload("TEST_TYPE"))
                {
                    data = static_cast<HModel>(*static_cast<SizeType*>(payload->Data));
                }
                OstGui::EndDragDropTarget();
            }

            OstGui::EndChild();

            OstGui::PopStyleColor();
        }
    } MODEL_HANDLE_PROPERTY_EDITOR;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------