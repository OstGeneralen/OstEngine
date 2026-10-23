// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIMainMenuItem.h"
#include "GUI/Layout/GUIPanel.h"

#include <string>

#include <Container/List.h>
#include <Container/Map.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GUILayout
    {
    public:
        template <typename T>
        T& SetRootPanel(const char* uniqueName);

        template <typename T>
        T& AddPanel(GUIPanel& parent, const char* uniqueName, const Vector2f& normalizedInitialSize);

        void PreWarmGUI(const Vector2f& renderSize, EditorContext& context);
        void DrawGUI(const Vector2f& renderSize, EditorContext& context);

    private:
        void BeginGUIDraw(const Vector2f& renderSize, EditorContext& context);
        void EndGUIDraw();

        void PreWarmPanelChildrenGUI(GUIPanel* pPanel, EditorContext& context);
        void DrawPanelChildren(GUIPanel* pPanel, EditorContext& context);

        void AddPanel(UniquePtr<GUIPanel>&& panel, const char* uniqueName, const Vector2f& normSize);

        GUIPanel* _pRootPanel;
        Map<std::string, UniquePtr<GUIPanel>> _panels;
    };

    // ------------------------------------------------------------
    // Impl

    template <typename T>
    inline T& GUILayout::SetRootPanel(const char* uniqueName)
    {
        UniquePtr<T> uPtr = Ptr::NewUnique<T>();
        T* tPtr = uPtr.Get();
        AddPanel(std::move(uPtr), uniqueName, {1, 1});
        _pRootPanel = tPtr;
        return *tPtr;
    }

    template <typename T>
    inline T& ost::GUILayout::AddPanel(GUIPanel& parent, const char* uniqueName, const Vector2f& normalizedInitialSize)
    {
        UniquePtr<T> uPtr = Ptr::NewUnique<T>();
        T* tPtr = uPtr.Get();
        parent._children.Add(tPtr);
        AddPanel(std::move(uPtr), uniqueName, normalizedInitialSize);
        return *tPtr;
    }

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------