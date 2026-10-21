// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    enum EGUIResize_ : Uint32
    {
        EGUIResize_None = 0,
        EGUIResize_X = 1 << 0,
        EGUIResize_Y = 1 << 1,
        EGUIResize_XY = EGUIResize_X | EGUIResize_Y
    };
    typedef Uint32 EGUIResize;

    class GUIControl
    {
    public:
        GUIControl(const std::string& uniqueID);
        virtual ~GUIControl();

        virtual void Display() = 0;
        virtual void PostDisplay() {}

    public:
        GUIControl& SetInitialSize( const Vector2f& size );
        GUIControl& SetResizeFlag(EGUIResize resizeFlag);
        GUIControl& SetBordered(bool bordered);
        GUIControl& SetPivot( const Vector2f& pivot );

        bool AllowResizeX() const;
        bool AllowResizeY() const;

        bool IsRoot() const;

        void MoveToRoot();
        void SetParent(GUIControl& parent);
        void AddChild(GUIControl& child);

        template <typename TCtrl, typename... TArgs>
        TCtrl& AddChild(TArgs&&... args)
        {
            TCtrl* ptr = new TCtrl(std::forward<TArgs>(args)...);
            AddChild(*ptr);
            return *ptr;
        }

        GUIControl* GetParent();
        const GUIControl* GetParent() const;

        List<GUIControl*>& GetChildren();
        const List<GUIControl*>& GetChildren() const;

        const std::string& GetUIDString() const;

    protected:
        void BeginGUI();
        void EndGUI();

    private:
        void EnsureSizeValidRange();

        Vector2f _size;
        Vector2f _pivot;

        std::string _uidString;
        List<GUIControl*> _pChildren;
        GUIControl* _pParent;
        Int32 _guiFlags;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------