// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorApplication.h"

#include "EditorContext.h"
#include "EditorGameInstance.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <windows.h>

#include <Engine/Configuration/RuntimeConfig.h>

// Windows
#include "GUI/Window/AboutWindow.h"

// Services
#include "Content/IconProvider.h"
#include "GUI/Controls/PropertyEditorDrawer.h"

using namespace ost;

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

EditorApplication::EditorApplication()
    : _hasExitRequest{false}
    , _window{}
    , _serviceLocator{}
    , _context{_serviceLocator}
    , _commandQueue{}
    , _coreEngine{}
    , _graphicsEngine{}
{
}

EditorApplication::~EditorApplication() = default;

void ost::EditorApplication::Start()
{
    RuntimeConfig config;
    config.LoadFromFile("EditorConfiguration.json");

    _window.Create(*this, "Ost Engine Editor", config.window.resolution, false);
    _graphicsEngine = IGraphicsEngine::Create(_serviceLocator, _window.GetNativeWindowHandle(), _window.GetClientSize());
    _coreEngine = IOstEngine::Create(_serviceLocator);

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

    IRenderHardwareInterface& rhi = _serviceLocator.GetRequired<IRenderHardwareInterface>();

    ID3D11Device* nativeDevice = reinterpret_cast<ID3D11Device*>(rhi.GetNativeDevice());
    ID3D11DeviceContext* nativeDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rhi.GetNativeContext());
    ImGui_ImplDX11_Init(nativeDevice, nativeDeviceContext);

    _window.AddNativeWindowEventCallback(&ImGuiWindowProcListener);

    // The editor registers the graphics engine as accessable service
    // This is to allow us to interact more closely with it
    _serviceLocator.RegisterUnmanaged<IGraphicsEngine>(_graphicsEngine.Get());
}

void ost::EditorApplication::Run()
{
    _coreEngine->SetGameInstance(&_editorGameInstance);

    _serviceLocator.RegisterManaged<PropertyEditorDrawer>(Ptr::NewUnique<PropertyEditorDrawer>());
    //_serviceLocator.RegisterManaged<IconProvider>(Ptr::NewUnique<IconProvider>());
    _serviceLocator.RegisterUnmanaged<IEditorGUI>(&_editorGui);
    IEditorGUI& winManager = _editorGui;
    winManager.RegisterWindowType<AboutWindow>();

    _serviceLocator.RegisterUnmanaged<SceneViewCamera>(&_sceneViewCamera);
    _serviceLocator.RegisterUnmanaged<IEditorCommandQueue>(&_commandQueue);

    _editorGui.Initialize();

    // Pre-warm the gui to calculate sizes from normalized to actual
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    _editorGui.PrewarmGUI(_window.GetClientSize().VectorCast<Float32>(), _context);

    while (!_hasExitRequest)
    {
        _commandQueue.Execute(_context);

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        _window.Update();

        _coreEngine->Tick();

        // Populate the render queue from the core engine's scene

        auto& renderQueue = _graphicsEngine->GetRenderQueue();
        auto& renderer = _graphicsEngine->GetRenderer();
        _coreEngine->RenderSceneGraph(renderQueue, renderer);
        _sceneViewCamera.InjectToRenderQueue(renderQueue, renderer);

        // Execute the command queue onto the output surface of the active renderer
        _graphicsEngine->ExecuteAndClearCommandQueue();

        // Intentionally left out since we actually don't want to render the output onto the backbuffer
        // It is instead drawn onto an image in the scene view
        _graphicsEngine->ClearAndSetBackbuffer();

        const Vector2f windowSize = _window.GetClientSize().VectorCast<Float32>();
        _editorGui.DisplayGUI(windowSize, _context);

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

    _graphicsEngine->SetOutputSize(_window.GetClientSize());
}

void ost::EditorApplication::ProcessKeyEvent(EKeyboard key, bool state)
{
    _coreEngine->GetInputReader().ProcessKeyEvent(key, state);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------