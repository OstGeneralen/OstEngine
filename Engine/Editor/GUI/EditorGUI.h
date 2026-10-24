// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUILayout.h"

#include <Container/List.h>
#include <Container/Map.h>
#include <Container/Queue.h>
#include <Math/Vector2.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class IGUIContextMenuOwner;
    class GUIWindow;

    class EditorGUI
    {
    public:
        void Initialize();
        void PrewarmGUI(const Vector2f& displaySize, EditorContext& context);
        void DisplayGUI(const Vector2f& displaySize, EditorContext& context);

        void OpenContextMenu(IGUIContextMenuOwner& contextMenuOwner);
        void CloseContextMenu();

        void RegisterWindowType(TypeID windowType, UniquePtr<GUIWindow>&& pWindow);

        void OpenWindow(TypeID windowType);
        void CloseWindow(TypeID windowType);

        const GUIWindow* GetWindow(TypeID windowType) const;
        // END IEditorGUI

    private:
        void DoOpenWindow(TypeID type, EditorContext& context);
        void DoCloseWindow(TypeID type, EditorContext& context);

        GUILayout _layout;

        // Context Menu
        IGUIContextMenuOwner* _pContextMenuOwner = nullptr;

        // Window management
        struct PendingWindowOp
        {
            bool isOpenOp;
            TypeID windowType;
        };

        GUIWindow* _pCurrentModalWindow = nullptr;
        Map<TypeID, GUIWindow*> _openWindows;

        Map<TypeID, UniquePtr<GUIWindow>> _windowRegistry;
        Queue<PendingWindowOp> _pendingWindowOpQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------