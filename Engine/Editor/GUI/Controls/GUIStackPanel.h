// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

// ------------------------------------------------------------

namespace ost
{
    enum class EOrientation
    {
        Horizontal,
        Vertical,
    };

    class GUIStackPanel : public GUIControl
    {
    public:
        GUIStackPanel(const std::string& uid, EOrientation orientation);

        void Display() override;

    private:
        EOrientation _orientation;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------