// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <imgui.h>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct GUIRect
    {
        Vector2f position;
        Vector2f size;
    };

    enum EGUIControlFlag : Uint32
    {
        EGUIControlFlag_None = 0,
        EGUIControlFlag_Dockable = 1 << 0,
        EGUIControlFlag_AllowChildren = 1 << 1,
    };
    typedef Uint32 EGUIControlFlag_;
    

    class GUIControl
    {
    public:
        friend class EditorGUI;

        // Controls must have a display function
        virtual void Display(const GUIRect& rect) = 0;

    protected:
        EGUIControlFlag_ controlFlags = EGUIControlFlag_None;

    private:
        void SetParent(GUIControl* pParent);
        void AddChild( GUIControl* pChild );

        std::string _name;
        GUIControl* _pParent = nullptr;
        List<GUIControl*> _children;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------