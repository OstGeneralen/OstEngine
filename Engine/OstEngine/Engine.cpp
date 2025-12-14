#include "Engine.h"

#include "EngineBuildFlags.h"
#include "EngineConfig.h"

#include <OstEngine/Debug/GUI/GUILogOutput.h>
#include <OstEngine/Debug/Logging/Logger.h>

#define DX_RENDERING 1
#if DX_RENDERING
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#include "Rendering/DX/DXRenderer.h"

#include <Windows.h>
#endif // DX

#include <OstEngine/ImGui/ImGuiHandling.h>
#include <OstEngine/Rendering/DX/EngineInfoGui.h>

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
    Logging::Confirm( "Window created with title '{}', resolution {}x{}", cfg.WindowTitle, cfg.Resolution.X,
                      cfg.Resolution.Y );

    _dxRenderer.Initialize( _window );
    clearColor = cfg.ClearColor;

    DeveloperGUI::Init( _window, _dxRenderer );

    _defaultRenderState = std::move(_dxRenderer.CreateRenderState( "Engine/Shaders/DefaultShader" ));

    _triA.AddVertex( { -0.5f, -0.5f, 0.f, 1.f }, 0x0000FFFF )
        .AddVertex( { 0.0f, 0.5f, 0.0f, 1.0f }, 0x00FF00FF )
        .AddVertex( { 0.5f, -0.5f, 0.0f, 1.0f }, 0xFF0000FF );

    _triA.InitializeResource();
}

void ost::CEngine::Deinitialize()
{
    DeveloperGUI::Deinit();

    _dxRenderer.Deinitialize();

    Logging::Confirm( "Engine shutdown complete, terminating process" );
}

void ost::CEngine::Run( IGame& aAppInterface )
{
    aAppInterface.Load();

    while ( _window.IsOpen() )
    {
        _inputReader.BeginFrame();
        _window.RunEventLoop();
        _inputSystem.Update( _inputReader );

        DeveloperGUI::BeginFrame();

        // ImGui::SetNextWindowPos( ImVec2{ 0, 0 } );
        // ImGui::SetNextWindowSize( ImGui::GetIO().DisplaySize );
        // ImGui::Begin( "Editor", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration |
        // ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove ); ImGui::Text( "OstEngine Application" );
        // ImGui::Indent( 20.0f );
        // ImGui::Text( "Adapter: %s", _dxRenderer.GetDebugInfo().AdapterName.c_str() );
        // ImGui::Text( "VRAM: %ugb", _dxRenderer.GetDebugInfo().VRAM );
        // ImGui::Indent( 0.0f );
        // ImGui::End();

        _dxRenderer.Clear( clearColor );

        // aAppInterface.Update();
        // aAppInterface.Render();

        _defaultRenderState.Bind();
        _triA.Render();
        //_defaultRenderState.Unbind();

        gui::GUI_LogOutput::DisplayStandalone();

        DeveloperGUI::EndFrame();

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


bool ost::CEngine::EngineEventProcessor( Uint32 aMsg, Int64 wparam, Uint64 lparam )
{
    if (DeveloperGUI::WndProcHandling(_window, aMsg, wparam, lparam))
    {
        return true;
    }

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
