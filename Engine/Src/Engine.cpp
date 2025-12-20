#include "OstEngine/Engine.h"

#include "OstEngine/EngineBuildFlags.h"
#include "Src/Debug/GUI/GUILogOutput.h"
#include "Src/EngineConfig.h"

#include "Src/Rendering/DX/DXOstEngineDefaults.h"

#include <OstEngine/Debug/Logging/Logger.h>

#define DX_RENDERING 1
#if DX_RENDERING
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

#include <Windows.h>
#endif // DX

#include "Src/ImGui/ImGuiHandling.h"

#include <OstEngine/Rendering/RenderCore.h>
#include <OstEngine/Utility/Timer.h>

#include <Src/Rendering/DX/DXHandling.h>
#include <Src/Rendering/DX/EngineInfoGui.h>

#include <OstEngine/Rendering/Camera.h>
#include <Src/Rendering/RenderData/EngineInputConstantBuffer.h>

ost::CEngine* ost::CEngine::_instancePtr = nullptr;
ost::SColor clearColor;
ost::CCamera defaultCamera;

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

    dx::Initialize( _window );
    dx::InitializeEngineDefaults();

    clearColor = cfg.ClearColor;

    DeveloperGUI::Init( _window );

    defaultCamera.InitializeOrthographic( { 16.0f, 9.0f } );
}

void ost::CEngine::Deinitialize()
{
    DeveloperGUI::Deinit();

    dx::Shutdown();

    Logging::Confirm( "Engine shutdown complete, terminating process" );
}

void ost::CEngine::Run( IGame& aAppInterface )
{
    CTimer frameTimer;
    
    aAppInterface.Load();

    Vector4f test;
    test.Magnitude();

    while ( _window.IsOpen() )
    {
        frameTimer.Update();

        _inputReader.BeginFrame();
        _window.RunEventLoop();
        _inputSystem.Update( _inputReader );

        dx::BeginRenderFrame( clearColor );
        
        // Update the constant buffer with the current camera and total time
        SEngineDataRenderInput worldData;
        worldData.ViewProjectionMatrix = aAppInterface.GetCamera().GetViewProjection();
        worldData.TotalTime = static_cast<Float32>( frameTimer.GetTotalTime() );
        worldData.SunDirection = aAppInterface.GetSunDirection();
        dx::UpdateEngineWorldData( worldData );

        aAppInterface.Update(frameTimer);
        aAppInterface.Render();

        DeveloperGUI::BeginFrame();
        // gui::GUI_LogOutput::DisplayStandalone();
        DeveloperGUI::EndFrame();

        dx::PresentRenderFrame();
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
    if ( DeveloperGUI::WndProcHandling( _window, aMsg, wparam, lparam ) )
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
//, _textureLoader(_renderer)
{
}
