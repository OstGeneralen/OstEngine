// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <imgui.h>

#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class PropertyEditor
    {
    public:
        virtual ~PropertyEditor() = default;

        virtual TypeID GetTargetTypeID() const = 0;
        virtual void Display(const char* name, void* pTarget)
        {
            ImGui::Text("Unsupported Property Type");
        }
    };

    template <typename T>
    class TypedPropertyEditor : public PropertyEditor
    {
    public:
        TypeID GetTargetTypeID() const override
        {
            return TypeID::Get<T>();
        }

        void Display(const char* name, void* pTarget) override
        {
            DisplayTyped(name, *static_cast<T*>(pTarget));
        }

        virtual void DisplayTyped(const char* name, T& target)
        {
            ImGui::Text("Unimplemented Property Type");
        }
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------