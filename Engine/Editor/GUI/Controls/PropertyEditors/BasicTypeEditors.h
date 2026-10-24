// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Controls/PropertyEditors/PropertyEditor.h"

#include <imgui.h>
#include <string>

#include <Math/Math.h>
#include <Memory/Memory.h>

// ------------------------------------------------------------

namespace ost
{
    class StringPropertyEditor : public PropertyTypeEditor<std::string>
    {
        void Display(const char* name, std::string& property)
        {
            char characters[128] = {'\0'};
            MemCopy(characters, property.c_str(), math::Min<SizeType>(128, property.length()));
            ImGui::InputText(name, characters, 128);
            property = characters;
        }
    } STRING_PROPERTY_EDITOR;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------