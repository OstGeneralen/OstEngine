#include "Engine.h"

#include "EngineBuildFlags.h"
#include "EngineConfig.h"

#define DX_RENDERING 1
#if DX_RENDERING
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#include "Rendering/DX/DXRenderer.h"

#include <Windows.h>
#endif // DX

#if ENABLE_GUI
#include <OstEngine/ImGui/imgui.h>
#include <OstEngine/ImGui/imgui_impl_dx11.h>
#include <OstEngine/ImGui/imgui_impl_win32.h>
#include <OstEngine/Rendering/DX/EngineInfoGui.h>
#endif

ost::CEngine* ost::CEngine::_instancePtr = nullptr;
ost::SColor clearColor;

ost::CEngine* ost::CEngine::Instance()
{
    return _instancePtr;
}

void ost::CEngine::InitializeEngine( HINSTANCE aAppInstance )
{
    _instancePtr = new CEngine();
    _instancePtr->Initialize( aAppInstance );
}

void ost::CEngine::ShutdownEngine()
{
    _instancePtr->Deinitialize();
    delete _instancePtr;
    _instancePtr = nullptr;
}

void ost::CEngine::Initialize( HINSTANCE aAppInstance )
{
    SEngineConfig cfg;
    cfg.LoadFromFile( "Engine/EngineConfig.json" );

    _window = std::move( CWindow( cfg.WindowTitle.c_str(), cfg.Resolution, aAppInstance ) );
    _window.BindEventCallback( [&]( auto m, auto w, auto l ) { return EngineEventProcessor( m, w, l ); } );

    _dxRenderer.Initialize( _window );
    clearColor = cfg.ClearColor;

#if ENABLE_GUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplWin32_Init( _window.GetWindowPointer().Get_AsIs<void*>() );
    ImGui_ImplDX11_Init( _dxRenderer.GetDevicePointer(), _dxRenderer.GetDeviceContextPointer() );
#endif
}

void ost::CEngine::Deinitialize()
{
#if ENABLE_GUI
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif

    _dxRenderer.Deinitialize();
}

void ost::CEngine::Run( IGame& aAppInterface )
{
    aAppInterface.Load();

    while ( _window.IsOpen() )
    {
        _inputReader.BeginFrame();
        _window.RunEventLoop();
        _inputSystem.Update( _inputReader );

#if ENABLE_GUI
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
#endif



        //ImGui::SetNextWindowPos( ImVec2{ 0, 0 } );
        //ImGui::SetNextWindowSize( ImGui::GetIO().DisplaySize );
        //ImGui::Begin( "Editor", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
        //ImGui::Text( "OstEngine Application" );
        //ImGui::Indent( 20.0f );
        //ImGui::Text( "Adapter: %s", _dxRenderer.GetDebugInfo().AdapterName.c_str() );
        //ImGui::Text( "VRAM: %ugb", _dxRenderer.GetDebugInfo().VRAM );
        //ImGui::Indent( 0.0f );
        //ImGui::End();

        _dxRenderer.Clear( clearColor );

        // aAppInterface.Update();
        // aAppInterface.Render();

#if ENABLE_GUI
        gui::DisplayEngineInfo( _dxRenderer );

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
#endif

        _dxRenderer.Present();
    }
}

ost::CInputSystem& ost::CEngine::GetInputSystem()
{
    return _inputSystem;
}

// ost::CRenderer& ost::CEngine::GetRenderer()
//{
//     //return _renderer;
// }
//
// ost::CTextureLoader& ost::CEngine::GetTextureLoader()
//{
//     //return _textureLoader;
// }

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
bool ost::CEngine::EngineEventProcessor( Uint32 aMsg, Int64 wparam, Uint64 lparam )
{
#if ENABLE_GUI
    if ( ImGui_ImplWin32_WndProcHandler( _window.GetWindowPointer().Get_AsIs<HWND>(), aMsg, wparam, lparam ) )
        return true;
#endif

    if ( _inputReader.ProcessInputEvent( aMsg, wparam, lparam ) )
    {
        return true;
    }

    switch ( aMsg )
    {
    case WM_CLOSE:
        _window.Close();
        break;
    default:
        break;
    }

    return false;
}

ost::CEngine::CEngine()
    : _window{}
    , _dxRenderer{}
//, _textureLoader(_renderer)
{
}
