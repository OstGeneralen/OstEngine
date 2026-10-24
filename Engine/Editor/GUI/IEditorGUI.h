// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/IGUIContextMenuOwner.h"

#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class GUIWindow;

    class IEditorGUI
    {
    public:
        template <typename T>
        void RegisterWindowType(UniquePtr<T>&& windowPtr)
        {
            RegisterWindowType(TypeID::Get<T>(), std::move(windowPtr));
        }

        template <typename T>
        void RegisterWindowType()
        {
            RegisterWindowType(TypeID::Get<T>(), Ptr::NewUnique<T>());
        }

        template <typename T>
        void OpenWindow()
        {
            OpenWindow(TypeID::Get<T>());
        }

        template <typename T>
        void CloseWindow()
        {
            CloseWindow(TypeID::Get<T>());
        }

        template <typename T>
        const T* GetWindow() const
        {
            return static_cast<const T*>(GetWindow(TypeID::Get<T>()));
        }

    public:
        // Open the context menu with the given owner for dispalying the GUI inside it

        virtual void OpenContextMenu(IGUIContextMenuOwner& contextMenuOwner) = 0;
        virtual void CloseContextMenu() = 0;

        // Window Management
        virtual void RegisterWindowType(TypeID windowType, UniquePtr<GUIWindow>&& pWindow) = 0;

        virtual void OpenWindow(TypeID windowType) = 0;
        virtual void CloseWindow(TypeID windowType) = 0;

        virtual const GUIWindow* GetWindow(TypeID windowType) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------