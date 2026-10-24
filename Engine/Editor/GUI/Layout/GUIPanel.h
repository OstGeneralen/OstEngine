// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIRect.h"
#include "GUI/OstGui.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    // Layout orientation determines the order child panels are drawn
    enum class EGuiLayoutOrientation
    {
        Vertical,   // Draw children top -> bottom
        Horizontal, // Draw children left -> right
        Default = Vertical,
    };

    // ------------------------------------------------------------

#define GUI_PANEL_OPTIONAL_OVERRIDE_VOID                                                                                                                                 \
    {                                                                                                                                                                    \
    }
#define GUI_PANEL_OPTIONAL_OVERRIDE_RETURN(r)                                                                                                                            \
    {                                                                                                                                                                    \
        return r;                                                                                                                                                        \
    }

    class GUIPanel
    {
    public:
        friend class GUILayout; // GUI Layout owns panels

        virtual ~GUIPanel() = default;

        // Present the gui itself. Each panel need this.
        virtual void DrawGUI(EditorContext& context) = 0;

    protected:
        // Optional overrides to change flags for child and window
        virtual ImGuiChildFlags GetDrawFlags() const GUI_PANEL_OPTIONAL_OVERRIDE_RETURN(0);
        virtual ImGuiWindowFlags GetWindowFlags() const GUI_PANEL_OPTIONAL_OVERRIDE_RETURN(0);

        void SetOrientation(EGuiLayoutOrientation orientation)
        {
            _orientation = orientation;
        }

    private:
        EGuiLayoutOrientation _orientation = EGuiLayoutOrientation::Default;
        List<GUIPanel*> _children;
        std::string _stringID;
        Vector2f _size;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------