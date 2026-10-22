// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUISceneView.h"

#include "EditorContext.h"

#include <imgui.h>

#include <Math/Color.h>

using namespace ost;

// ------------------------------------------------------------

GUISceneView::GUISceneView()
    : GUIControl("##OGUISceneView")
    , _displayTexture{static_cast<Uint32>(ERenderOutputTexture::Output)}
    , _cachedSceneRenderSize{}

{
}

void GUISceneView::Display()
{
    IGraphicsEngine& gfxEngine = EditorContext::Get().serviceLocator.GetRequired<IGraphicsEngine>();
    const IRenderer& renderer = gfxEngine.GetRenderer();

    auto showMenuItem = [](const char* l, ERenderOutputTexture t, Uint32& outSelected) {
        if (ImGui::MenuItem(l, 0, false, outSelected != static_cast<Uint32>(t)))
        {
            outSelected = static_cast<Uint32>(t);
        }
    };

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
    BeginGUI(ImGuiWindowFlags_MenuBar);
    ImGui::PopStyleVar();

    ImGui::BeginMenuBar();

    ImGui::TextColored(Colors::Yellow.Vec4, "Scene View");
    ImGui::Separator();

    if (ImGui::BeginMenu("Output"))
    {
        showMenuItem("Unlit", ERenderOutputTexture::GBufferAlbedo, _displayTexture);
        showMenuItem("Lit", ERenderOutputTexture::Output, _displayTexture);
        ImGui::Separator();
        showMenuItem("Normals", ERenderOutputTexture::GBufferNormal, _displayTexture);
        showMenuItem("ORM", ERenderOutputTexture::GBufferORM, _displayTexture);
        showMenuItem("Depth", ERenderOutputTexture::Depth, _displayTexture);

        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();

    const Vector2u activeRenderSize = Vector2f(ImGui::GetContentRegionAvail()).VectorCast<Uint32>();

    const void* pNativeTexture = renderer.GetOutputTarget(static_cast<ERenderOutputTexture>(_displayTexture))->GetNativeResource();
    ImGui::Image((ImTextureRef)(intptr_t)pNativeTexture, gfxEngine.GetRenderer().GetDimensions());

    EndGUI();

    _desiredRenderSize = activeRenderSize;
}

void ost::GUISceneView::PostDisplay()
{
    if (_cachedSceneRenderSize != _desiredRenderSize)
    {
        IGraphicsEngine& gfxEngine = EditorContext::Get().serviceLocator.GetRequired<IGraphicsEngine>();
        gfxEngine.SetRenderSize(_desiredRenderSize);
        _cachedSceneRenderSize = _desiredRenderSize;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------