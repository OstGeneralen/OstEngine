#include "Engine.h"
#include "EngineConfig.h"

#define DX_RENDERING 1
#if DX_RENDERING
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#include "Rendering/DX/DXRenderer.h"
#include <Windows.h>
#endif // DX


ost::CEngine* ost::CEngine::_instancePtr = nullptr;
ost::SColor clearColor;

ost::CEngine* ost::CEngine::Instance()
{
    return _instancePtr;
}

void ost::CEngine::InitializeEngine( HINSTANCE aAppInstance )
{
    _instancePtr = new CEngine();
    _instancePtr->Initialize(aAppInstance);
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
}

void ost::CEngine::Deinitialize()
{
    _dxRenderer.Deinitialize();
}

void ost::CEngine::Run( IGame& aAppInterface )
{
    aAppInterface.Load();

    while (_window.IsOpen())
    {
        _inputReader.BeginFrame();
        _window.RunEventLoop();
        _inputSystem.Update( _inputReader );

        _dxRenderer.Clear( clearColor );

        //aAppInterface.Update();
        //aAppInterface.Render();

        _dxRenderer.Present();
    }
}

ost::CInputSystem& ost::CEngine::GetInputSystem()
{
    return _inputSystem;
}

//ost::CRenderer& ost::CEngine::GetRenderer()
//{
//    //return _renderer;
//}
//
//ost::CTextureLoader& ost::CEngine::GetTextureLoader()
//{
//    //return _textureLoader;
//}

bool ost::CEngine::EngineEventProcessor( Uint32 aMsg, Int64 wparam, Uint64 lparam )
{
    if (_inputReader.ProcessInputEvent(aMsg, wparam, lparam))
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
