// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GUIControl
    {
    public:
        GUIControl(const std::string& uniqueID);
        virtual ~GUIControl();

        virtual void Display() = 0;

        virtual bool AllowResizeX() const
        {
            return false;
        }
        virtual bool AllowResizeY() const
        {
            return false;
        }

    public:
        bool IsRoot() const;

        void MoveToRoot();
        void SetParent(GUIControl& parent);
        void AddChild(GUIControl& child);

        GUIControl* GetParent();
        const GUIControl* GetParent() const;

        List<GUIControl*>& GetChildren();
        const List<GUIControl*>& GetChildren() const;

        const std::string& GetUIDString() const;

    protected:
        Vector2f size;

    private:
        std::string _uidString;
        List<GUIControl*> _pChildren;
        GUIControl* _pParent;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------