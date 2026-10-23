// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIRect.h"

#include <OstTypes.h>
#include <imgui.h>
#include <string>

#include <Container/List.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorContext;

    // Layout orientation determines the order child panels are drawn
    enum class EGuiLayoutOrientation
    {
        Horizontal, // Draw children left -> right
        Vertical,   // Draw children top -> bottom
    };

    // ------------------------------------------------------------

    class GUIPanel
    {
    public:
        friend class GUILayout; // GUI Layout owns panels

        virtual ~GUIPanel() = default;

        // Present the gui itself
        virtual void DrawGUI(EditorContext& context) = 0;

        // Get the child flags
        virtual ImGuiChildFlags GetDrawFlags() const;

        // Size pointer access to pass into ImGuis sizing function
        Vector2f& GetSizeRef();

    private:
        EGuiLayoutOrientation _orientation = EGuiLayoutOrientation::Vertical;
        List<GUIPanel*> _children;
        std::string _stringID;
        Vector2f _size;
    };

    // ------------------------------------------------------------
    // IMPL

    inline ImGuiChildFlags GUIPanel::GetDrawFlags() const
    {
        return 0;
    }

    inline Vector2f& ost::GUIPanel::GetSizeRef()
    {
        return _size;
    }
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------