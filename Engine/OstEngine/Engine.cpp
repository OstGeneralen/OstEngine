#include "Engine.h"
#include "EngineConfig.h"

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

    _window = std::move( CWindow( cfg.WindowTitle.c_str(), cfg.Resolution ) );
    _renderer.Initialize(_window, cfg.ClearColor);
}

void ost::CEngine::Deinitialize()
{
    _renderer.Deinitialize();
}

void ost::CEngine::Run( IApplication& aAppInterface )
{
    aAppInterface.Load();

    while (_window.IsOpen())
    {
        _window.RunEventLoop();

        _renderer.BeginFrame();

        aAppInterface.Update();
        aAppInterface.Render();

        _renderer.EndFrame();
    }
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
