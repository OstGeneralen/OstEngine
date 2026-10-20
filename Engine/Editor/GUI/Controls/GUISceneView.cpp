// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUISceneView.h"

#include "EditorContext.h"

#include <imgui.h>

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
    const IRenderer& renderer = EditorContext::Get().graphicsEngine.GetRenderer();

    BeginGUI();

    ImGui::BeginGroup();
    if (ImGui::Button("Depth"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::Depth);
    }
    ImGui::SameLine();
    if (ImGui::Button("Color"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::GBufferAlbedo);
    }
    ImGui::SameLine();
    if (ImGui::Button("Lit"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::Output);
    }
    ImGui::EndGroup();

    ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, {0,0} );
    ImGui::BeginChild( "##SceneViewRender", {0,0}, ImGuiChildFlags_Borders );
    ImGui::PopStyleVar();
    const Vector2u activeRenderSize = Vector2f( ImGui::GetContentRegionAvail() ).VectorCast<Uint32>();

    const void* pNativeTexture = renderer.GetOutputTarget(static_cast<ERenderOutputTexture>(_displayTexture))->GetNativeResource();
    ImGui::Image( (ImTextureRef)(intptr_t)pNativeTexture, activeRenderSize.VectorCast<Float32>() );

    ImGui::EndChild();

    EndGUI();

    if(activeRenderSize != _cachedSceneRenderSize)
    {
        EditorContext::Get().graphicsEngine.SetRenderSize( activeRenderSize );
        _cachedSceneRenderSize = activeRenderSize;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------