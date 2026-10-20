// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

#include <OstTypes.h>

#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GUILayout
    {
    public:
        GUILayout();
        
        void Display(const Vector2f& fullSize);


    private:
        void DisplayTopMenu();
    
        UniquePtr<GUIControl> _rootElement;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------