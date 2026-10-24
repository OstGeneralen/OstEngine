// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/EditorGUI.h"
#include "GUI/Controls/PropertyEditorDrawer.h"

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class GUIContext
    {
    public:
        GUIContext(EditorContext& parentCtx, EditorGUI& gui);

        // clang-format off
        // Window Template helpers
        template<typename T> void RegisterWindowType();
        template<typename T> void OpenWindow();
        template<typename T> void CloseWindow();
        template<typename T> const T* GetWindow() const;
        // clang-format on

        void OpenWindow(TypeID windowType);
        void CloseWindow(TypeID windowType);

        void OpenContextMenu(IGUIContextMenuOwner& menuOwner);
        void CloseContextMenu();

        PropertyEditorDrawer propertyDrawer;

    private:
        EditorContext& _parentContext;
        EditorGUI& _gui;
    };

    template <typename T>
    inline void ost::GUIContext::RegisterWindowType()
    {
        _gui.RegisterWindowType(TypeID::Get<T>(), Ptr::NewUnique<T>());
    }

    template <typename T>
    inline void ost::GUIContext::OpenWindow()
    {
        _gui.OpenWindow(TypeID::Get<T>());
    }

    template <typename T>
    inline void ost::GUIContext::CloseWindow()
    {
        _gui.CloseWindow(TypeID::Get<T>());
    }

    template <typename T>
    inline const T* ost::GUIContext::GetWindow() const
    {
        return static_cast<const T*>(_gui.GetWindow(TypeID::Get<T>()));
    }
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------