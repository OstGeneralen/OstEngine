#include "Engine.h"

ost::CEngine* ost::CEngine::_instancePtr = nullptr;

ost::CEngine* ost::CEngine::Instance()
{
    return _instancePtr;
}

void ost::CEngine::InitializeRendering( CWindow& appWindow )
{
    _renderer.Initialize( appWindow );
}

void ost::CEngine::Deinitialize()
{
    _renderer.Deinitialize();
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
    : _renderer{}
    , _textureLoader(_renderer)
{
}
