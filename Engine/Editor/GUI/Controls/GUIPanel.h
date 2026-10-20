// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

// ------------------------------------------------------------

namespace ost
{
    class GUIPanel : public GUIControl
    {
    public:
        GUIPanel(const std::string& uidString);

        void Display() override;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------