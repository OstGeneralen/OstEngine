// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorApplication.h"

#include "EditorContext.h"
#include "EditorGameInstance.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <windows.h>

// ------------------------------------------------------------

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

bool ImGuiWindowProcListener(const ost::NativeWindowEventContext& ctx)
{
    if (ImGui_ImplWin32_WndProcHandler(static_cast<HWND>(ctx.nativeWindowHandle), ctx.message, ctx.wParam, ctx.lParam))
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------

void ost::EditorApplication::Start()
{
    RuntimeConfig config;
    config.LoadFromFile("EditorConfiguration.json");

    _window.Create(*this, "Ost Engine Editor", config.window.resolution, false);

    GraphicsEngineSettings gfxEngineSettings;
    gfxEngineSettings.output.clientSize = _window.GetClientSize();
    gfxEngineSettings.output.fullscreen = false;
    gfxEngineSettings.output.nativeWindowHandle = _window.GetNativeWindowHandle();
    gfxEngineSettings.output.renderSize = config.rendering.renderScale;
    gfxEngineSettings.renderer.rendererType = ERendererType::Deferred;
    gfxEngineSettings.renderer.clearColor = Colors::Black;
    _graphicsEngine = IGraphicsEngine::CreateNew(gfxEngineSettings);

    OstEngineSettings coreEngineSettings;
    coreEngineSettings.pGfxEngine = _graphicsEngine.Get();
    coreEngineSettings.assetsCfg = config.assets;
    _coreEngine = IOstEngine::CreateNew(Ptr::NewUnique<EditorGameInstance>(), coreEngineSettings);

    // Initializ ImGui
    ImGui_ImplWin32_EnableDpiAwareness();
    Float32 mainScale = ImGui_ImplWin32_GetDpiScaleForHwnd(_window.GetNativeWindowHandle());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;

    style.ScaleAllSizes(mainScale);
    style.FontScaleDpi = mainScale;

    ImGui_ImplWin32_Init(_window.GetNativeWindowHandle());

    ID3D11Device* nativeDevice = reinterpret_cast<ID3D11Device*>(_graphicsEngine->GetRenderHardwareInterface().GetNativeDevice());
    ID3D11DeviceContext* nativeDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(_graphicsEngine->GetRenderHardwareInterface().GetNativeContext());
    ImGui_ImplDX11_Init(nativeDevice, nativeDeviceContext);

    _window.AddNativeWindowEventCallback(&ImGuiWindowProcListener);

    EditorContext::Create(*_coreEngine, *_graphicsEngine, _window);
}

#include "Panel/AssetsPanel.h"

void ost::EditorApplication::Run()
{
    while (!_hasExitRequest)
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        _window.Update();

        _coreEngine->Tick();
        _graphicsEngine->ExecuteAndClearCommandQueue();
        _graphicsEngine->DrawRendererOutput();

        AssetsPanel panel;
        panel.Draw();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        _graphicsEngine->Present();
    }
}

void ost::EditorApplication::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    EditorContext::Destroy();

    _coreEngine = nullptr;
    _graphicsEngine = nullptr;
    _window.Close();
}

void ost::EditorApplication::RequestExit()
{
    _hasExitRequest = true;
}

void ost::EditorApplication::Resized()
{
    if (!_graphicsEngine)
    {
        return;
    }

    GraphicsEngineSettings gfxEngSettings;
    gfxEngSettings.renderer.clearColor = Colors::Black;
    gfxEngSettings.renderer.rendererType = ERendererType::Deferred;
    gfxEngSettings.output.clientSize = _window.GetClientSize();
    gfxEngSettings.output.renderSize = {1.0f, 1.0f};
    gfxEngSettings.output.nativeWindowHandle = _window.GetNativeWindowHandle();
    gfxEngSettings.output.fullscreen = false;

    _graphicsEngine->UpdateSettings(gfxEngSettings);
}

void ost::EditorApplication::ProcessKeyEvent(EKeyboard key, bool state)
{
    _coreEngine->GetInputReader().ProcessKeyEvent(key, state);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------