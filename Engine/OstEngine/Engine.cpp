#include "Engine.h"
#include "EngineConfig.h"
#include <SDL3/SDL.h>

ost::CEngine* ost::CEngine::_instancePtr = nullptr;

ost::CEngine* ost::CEngine::Instance()
{
    return _instancePtr;
}

void ost::CEngine::InitializeEngine()
{
    _instancePtr = new CEngine();
    _instancePtr->Initialize();
}

void ost::CEngine::ShutdownEngine()
{
    _instancePtr->Deinitialize();
    delete _instancePtr;
    _instancePtr = nullptr;
}

void ost::CEngine::Initialize()
{
    SEngineConfig cfg;
    cfg.LoadFromFile( "Engine/EngineConfig.json" );

    SDL_Init( SDL_INIT_VIDEO );
    SDL_SetHint( SDL_HINT_RENDER_DRIVER, "direct3d12" );


    _window = std::move( CWindow( cfg.WindowTitle.c_str(), cfg.Resolution ) );
    _renderer.Initialize(_window, cfg.ClearColor);
}

void ost::CEngine::Deinitialize()
{
    _renderer.Deinitialize();
}

void ost::CEngine::Run( IGame& aAppInterface )
{
    aAppInterface.Load();

    while (_window.IsOpen())
    {
        _inputReader.BeginFrame();
        _window.RunEventLoop(_inputReader);
        _inputSystem.Update( _inputReader );

        _renderer.BeginFrame();

        aAppInterface.Update();
        aAppInterface.Render();

        _renderer.EndFrame();
    }
}

ost::CInputSystem& ost::CEngine::GetInputSystem()
{
    return _inputSystem;
}

ost::CRenderer& ost::CEngine::GetRenderer()
{
    return _renderer;
}

ost::CTextureLoader& ost::CEngine::GetTextureLoader()
{
    return _textureLoader;
}

ost::CEngine::CEngine()
    : _window{}
    , _renderer{}
    , _textureLoader(_renderer)
{
}
