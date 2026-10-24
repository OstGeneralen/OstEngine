// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Controls/PropertyEditors/PropertyEditor.h"

#include <imgui.h>

#include <Math/Color.h>
#include <Math/Units.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    class Float32PropertyEditor : public PropertyTypeEditor<Float32>
    {
        void Display(const char* name, Float32& data) override
        {
            ImGui::DragFloat(name, &data, 0.1f);
        }
    } FLOAT32_PROPERTY_EDITOR;

    class Int32PropertyEditor : public PropertyTypeEditor<Int32>
    {
        void Display(const char* name, Int32& data) override
        {
            ImGui::InputInt(name, &data);
        }
    } INT32_PROPERTY_EDITOR;

    class Vector2fPropertyEditor : public PropertyTypeEditor<Vector2f>
    {
        void Display(const char* name, Vector2f& data) override
        {
            ImGui::DragFloat2(name, data.Arr, 0.1f);
        }
    } VEC2F_PROPERTY_EDITOR;

    class Vector3fPropertyEditor : public PropertyTypeEditor<Vector3f>
    {
        void Display(const char* name, Vector3f& data) override
        {
            ImGui::DragFloat3(name, data.Arr, 0.1f);
        }
    } VEC3F_PROPERTY_EDITOR;

    class Vector4fPropertyEditor : public PropertyTypeEditor<Vector4f>
    {
        void Display(const char* name, Vector4f& data) override
        {
            ImGui::DragFloat4(name, data.Arr, 0.1f);
        }
    } VEC4F_PROPERTY_EDITOR;

    class ColorPropertyEditor : public PropertyTypeEditor<Color>
    {
        void Display(const char* name, Color& data) override
        {
            ImGui::ColorEdit4(name, data.FltArray, 0.1f);
        }
    } COLOR_PROPERTY_EDITOR;

    class RadiansPropertyEditor : public PropertyEditor
    {
        virtual TypeID PropertyTypeID() const override
        {
            return TypeID::Get<Radians>();
        }

        void DisplayGeneric(const char* name, void* pGeneric) override
        {
            Float32* asFloat = static_cast<Float32*>(pGeneric);
            Float32 degrees = (*asFloat) * math::RadToDeg;

            ImGui::DragFloat(name, &degrees, 0.01f, 0.0f, 360.0f);

            (*asFloat) = degrees * math::DegToRad;
        }

    } RADIANS_PROPERTY_EDITOR;

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------