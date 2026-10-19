// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "PropertyEditors/PropertyEditor.h"

#include <imgui.h>
#include <string>

#include <Math/Color.h>
#include <Math/Math.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Memory/Memory.h>

// ------------------------------------------------------------

namespace ost
{
    class TextPropertyEditor : public TypedPropertyEditor<std::string>
    {
        void DisplayTyped(const char* name, std::string& property) override
        {
            char buffer[128] = {0};
            MemCopy(buffer, property.data(), math::Min<SizeType>(property.size(), 128));

            if (ImGui::InputText(name, buffer, 128))
            {
                property = buffer;
            }
        }
    };

    class FloatPropertyEditor : public TypedPropertyEditor<Float32>
    {
        void DisplayTyped(const char* name, Float32& property) override
        {
            ImGui::InputFloat(name, &property);
        }
    };

    class Vector2fPropertyEditor : public TypedPropertyEditor<Vector2f>
    {
        void DisplayTyped(const char* name, Vector2f& property) override
        {
            ImGui::InputFloat2(name, property.Arr);
        }
    };

    class Vector3fPropertyEditor : public TypedPropertyEditor<Vector3f>
    {
        void DisplayTyped(const char* name, Vector3f& property) override
        {
            ImGui::InputFloat3(name, property.Arr);
        }
    };

    class Vector4fPropertyEditor : public TypedPropertyEditor<Vector4f>
    {
        void DisplayTyped(const char* name, Vector4f& property) override
        {
            ImGui::InputFloat4(name, property.Arr);
        }
    };

    class ColorPropertyEditor : public TypedPropertyEditor<Color>
    {
        void DisplayTyped(const char* name, Color& property) override
        {
            ImGui::ColorEdit4(name, property.FltArray);
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------