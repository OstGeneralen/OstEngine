// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUISceneView.h"

#include "EditorContext.h"
#include "SceneView/SceneViewCamera.h"

#include <imgui.h>

#include <Math/Color.h>

// Engine
#include <Engine/System/IInputReader.h>
#include <Engine/System/ITimeProvider.h>

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

    if (_isFlyMode)
    {
        ImGui::PushStyleColor(ImGuiCol_Border, {0, 1, 1, 1});
    }

    BeginGUI(ImGuiWindowFlags_MenuBar);

    if (_isFlyMode)
    {
        ImGui::PopStyleColor();
    }

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

    const Vector2f min = ImGui::GetItemRectMin();
    const Vector2f max = ImGui::GetItemRectMax();
    const Vector2f mousePos = ImGui::GetMousePos();
    const bool mouseOutside = mousePos.X < min.X || mousePos.Y < min.Y || mousePos.X > max.X || mousePos.Y > max.Y;
    if (!mouseOutside && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        _isFlyMode = true;
        _cachedMousePos = ImGui::GetMousePos();
    }
    else if (_isFlyMode && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
    {
        _isFlyMode = false;
    }

    if (_isFlyMode)
    {
        UpdateFlyMode();
    }

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

void ost::GUISceneView::UpdateFlyMode()
{
    const Float32 sensitivity = 0.8f;

    SceneViewCamera& sceneViewCamera = EditorContext::Get().serviceLocator.GetRequired<SceneViewCamera>();
    IInputReader& input = EditorContext::Get().serviceLocator.GetRequired<IInputReader>();
    ITimeProvider& time = EditorContext::Get().serviceLocator.GetRequired<ITimeProvider>();

    const Vector2f currentMousePos = ImGui::GetMousePos();
    Vector2f mouseDelta = (currentMousePos - _cachedMousePos) * sensitivity;
    _cachedMousePos = currentMousePos;

    sceneViewCamera.LookLeftRight(mouseDelta.X);
    sceneViewCamera.LookUpDown(mouseDelta.Y);

    Vector3f translationDirection;

    if (input.Down(EKeyboard::W))
    {
        translationDirection.Z += 1;
    }
    if (input.Down(EKeyboard::S))
    {
        translationDirection.Z -= 1;
    }
    if (input.Down(EKeyboard::D))
    {
        translationDirection.X += 1;
    }
    if (input.Down(EKeyboard::A))
    {
        translationDirection.X -= 1;
    }
    if (input.Down(EKeyboard::Space))
    {
        translationDirection.Y += 1;
    }
    if (input.Down(EKeyboard::LCtrl))
    {
        translationDirection.Y -= 1;
    }
    translationDirection.Normalize();

    sceneViewCamera.Move(translationDirection * 2.0f * time.GetDeltaTime());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------