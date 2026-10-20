// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneView.h"

#include "EditorContext.h"

#include <imgui.h>

#include <GraphicsEngine/Rendering/IRenderer.h>

using namespace ost;

// ------------------------------------------------------------

SceneView::SceneView()
{
    _displayTexture = static_cast<Uint32>(ERenderOutputTexture::Output);
}

void ost::SceneView::Display()
{
    ImGui::BeginGroup();
    if (ImGui::Button("Lit"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::Output);
    }
    ImGui::SameLine();
    if (ImGui::Button("Normal"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::GBufferNormal);
    }
    ImGui::SameLine();
    if (ImGui::Button("ORM"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::GBufferORM);
    }
    ImGui::SameLine();
    if (ImGui::Button("Depth"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::Depth);
    }
    ImGui::SameLine();
    if (ImGui::Button("Unlit"))
    {
        _displayTexture = static_cast<Uint32>(ERenderOutputTexture::GBufferAlbedo);
    }
    ImGui::EndGroup();

    ImGui::BeginChild("SceneView##Internal", ImGui::GetContentRegionAvail());

    const Vector2f sceneRenderSize = ImGui::GetContentRegionAvail();
    const Vector2u sceneRenderSizeUint = sceneRenderSize.VectorCast<Uint32>();
    
    const ITexture* pOutputTexture = EditorContext::Get().graphicsEngine.GetRenderer().GetOutputTarget(static_cast<ERenderOutputTexture>(_displayTexture));
    ImGui::Image((ImTextureID)(intptr_t)pOutputTexture->GetNativeResource(), sceneRenderSize);
    
    ImGui::EndChild();
    
    if(sceneRenderSizeUint != _cachedSize)
    {
        EditorContext::Get().graphicsEngine.SetRenderSize(sceneRenderSizeUint);
        _cachedSize = sceneRenderSizeUint;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------