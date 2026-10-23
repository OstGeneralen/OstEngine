// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUILayout.h"
#include "GUI/Window/IGUIWindowManager.h"

#include <Container/List.h>
#include <Container/Map.h>
#include <Container/Queue.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorGUI : public IGUIWindowManager
    {
    public:
        void Initialize();
        void PrewarmGUI(const Vector2f& displaySize, EditorContext& context);
        void DisplayGUI(const Vector2f& displaySize, EditorContext& context);

        // BEGIN IGUIWindowManager
        void RegisterWindowType(TypeID windowType, UniquePtr<GUIWindow>&& pWindow) override;

        void OpenWindow(TypeID windowType) override;
        void CloseWindow(TypeID windowType) override;

        const GUIWindow* GetWindow(TypeID windowType) const override;
        // END IGUIWindowManager

    private:
        void DoOpenWindow(TypeID type, EditorContext& context);
        void DoCloseWindow(TypeID type, EditorContext& context);

        GUILayout _layout;

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