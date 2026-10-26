// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorGUI.h"

#include "EditorContext.h"
#include "GUI/Layout/GUIStackPanel.h"

// Window
#include "GUI/Window/GUIWindow.h"

// Actual Windows/Panels
#include "Editors/AssetView/AssetDirectoryListGUIPanel.h"
#include "Editors/AssetView/AssetViewGUIPanel.h"
#include "Editors/PropertyEditor/PropertyEditorGUIPanel.h"
#include "Editors/SceneOutliner/SceneOutlinerGUIPanel.h"
#include "Editors/SceneView/SceneViewGUIPanel.h"

// Windows
#include "Editors/PropertyEditor/Windows/AddComponentPromptWindow.h"
#include "GUI/Prompts/DirectorySelectWindow.h"
#include "GUI/Window/AboutWindow.h"

using namespace ost;

// ------------------------------------------------------------

void ost::EditorGUI::Initialize()
{
    // Set up panel layout
    auto& root = _layout.SetRootPanel<GUIStackPanel>("GUIRoot").SetOrientation(EGuiLayoutOrientation::Vertical);
    auto& upper = _layout.AddPanel<GUIStackPanel>(root, "GUITop", {0, 0.75f}).SetOrientation(EGuiLayoutOrientation::Horizontal);
    auto& lower = _layout.AddPanel<GUIStackPanel>(root, "GUIBottom", {0, 0.25f}).SetOrientation(EGuiLayoutOrientation::Horizontal);

    _layout.AddPanel<SceneOutlinerPanel>(upper, "GUISceneOutliner", {0.125f, 0});
    _layout.AddPanel<SceneViewGUIPanel>(upper, "GUISceneView", {0.75f, 0});
    _layout.AddPanel<PropertyEditorGUIPanel>(upper, "GUIPropertyEditor", {0.125f, 0});

    _layout.AddPanel<AssetDirectoryListGUIPanel>(lower, "GUIAssetDirView", {0.125f, 0});
    _layout.AddPanel<AssetViewGUIPanel>(lower, "GUIAssetView", {0.875f, 0});
}

void ost::EditorGUI::PrewarmGUI(const Vector2f& displaySize, EditorContext& context)
{
    // Before prewarming, register all the window types
    context.guiContext.RegisterWindowType<AboutWindow>();
    context.guiContext.RegisterWindowType<AddComponentPromptWindow>();
    context.guiContext.RegisterWindowType<DirectorySelectWindow>();

    // Prewarm
    _layout.PreWarmGUI(displaySize, context);
}

void ost::EditorGUI::DisplayGUI(const Vector2f& displaySize, EditorContext& context)
{
    // Process window operations
    PendingWindowOp windowOp;
    while (_pendingWindowOpQueue.TryPop(windowOp))
    {
        if (windowOp.isOpenOp)
        {
            DoOpenWindow(windowOp.windowType, context);
        }
        else if (windowOp.isOpenOp == false)
        {
            DoCloseWindow(windowOp.windowType, context);
        }
    }

    const IGUIContextMenuOwner* previousContextMenuOwner = _pContextMenuOwner;

    // Display the layout GUI
    ImGui::BeginDisabled(_pCurrentModalWindow != nullptr);
    _layout.DrawGUI(displaySize, context);

    if (previousContextMenuOwner == nullptr && _pContextMenuOwner != nullptr)
    {
        ImGui::OpenPopup("GUIEditorContextMenu");
    }

    // Display the context menu if its open
    if (_pContextMenuOwner && ImGui::BeginPopup("GUIEditorContextMenu"))
    {
        _pContextMenuOwner->DrawContextMenuGUI(context);
        ImGui::EndPopup();
    }
    else
    {
        // If the popup isn't open any more, remove the context menu owner
        _pContextMenuOwner = nullptr;
    }

    // Display open windows
    for (auto& [type, pWin] : _openWindows)
    {
        // Skip modal here! We want to draw modal last.
        if (pWin == _pCurrentModalWindow)
            continue;

        pWin->DrawGUI(context);
    }
    ImGui::EndDisabled();

    // Lastly, display modal window
    if (_pCurrentModalWindow)
    {
        _pCurrentModalWindow->DrawGUI(context);
    }
}

// ------------------------------------------------------------

void ost::EditorGUI::OpenContextMenu(IGUIContextMenuOwner& contextMenuOwner)
{
    _pContextMenuOwner = &contextMenuOwner;
}

void ost::EditorGUI::CloseContextMenu()
{
    _pContextMenuOwner = nullptr;
}

// ------------------------------------------------------------

void ost::EditorGUI::RegisterWindowType(TypeID windowType, UniquePtr<GUIWindow>&& pWindow)
{
    _windowRegistry.Insert(windowType, std::move(pWindow));
}

void ost::EditorGUI::OpenWindow(TypeID windowType)
{
    PendingWindowOp op;
    op.isOpenOp = true;
    op.windowType = windowType;
    _pendingWindowOpQueue.Push(op);
}

void ost::EditorGUI::CloseWindow(TypeID windowType)
{
    PendingWindowOp op;
    op.isOpenOp = false;
    op.windowType = windowType;
    _pendingWindowOpQueue.Push(op);
}

const GUIWindow* EditorGUI::GetWindow(TypeID windowType) const
{
    if (const UniquePtr<GUIWindow>* ppWindow = _windowRegistry.TryGetValue(windowType))
    {
        return ppWindow->Get();
    }
    return nullptr;
}

// ------------------------------------------------------------

void EditorGUI::DoOpenWindow(TypeID type, EditorContext& context)
{
    if (_openWindows.Contains(type))
    {
        // Early out! This window is already open
        return;
    }

    if (UniquePtr<GUIWindow>* found = _windowRegistry.TryGetValue(type))
    {
        GUIWindow* pWindow = found->Get();
        _openWindows.Insert(type, pWindow);
        pWindow->OnOpen(context);

        if (pWindow->GetWindowMode() == EGuiWindowMode::Modal)
        {
            _pCurrentModalWindow = pWindow;
        }
    }
}

void EditorGUI::DoCloseWindow(TypeID type, EditorContext& context)
{
    if (GUIWindow** ppWindow = _openWindows.TryGetValue(type))
    {
        GUIWindow* pWindow = *ppWindow;
        pWindow->OnClose(context);
        if (pWindow == _pCurrentModalWindow)
        {
            _pCurrentModalWindow = nullptr;
        }
        _openWindows.Remove(type);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
