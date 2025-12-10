#include "Texture.h"

#include "../Renderer.h"

#include <SDL3/SDL.h>
#include <cassert>

// ------------------------------------------------------------

ost::STexture::STexture()
    : _sdlSurfacePtr{ nullptr }
    , _sdlTexturePtr{ nullptr }
{
}

// ------------------------------------------------------------

ost::STexture::STexture( const std::string& aPath, CRenderer& aRenderer )
    : STexture()
{
    LoadFromFile( aPath, aRenderer );
}

// ------------------------------------------------------------

ost::STexture::STexture( STexture&& aOther ) noexcept
{
    _sdlSurfacePtr = aOther._sdlSurfacePtr;
    _sdlTexturePtr = aOther._sdlTexturePtr;
    aOther._sdlSurfacePtr = nullptr;
    aOther._sdlTexturePtr = nullptr;
}

// ------------------------------------------------------------

ost::STexture::~STexture()
{
}

// ------------------------------------------------------------

ost::STexture& ost::STexture::operator=( STexture&& aOther ) noexcept
{
    assert( _sdlSurfacePtr == nullptr && "Surface is not null! Don't move a texture into an initalized texture." );
    assert( _sdlTexturePtr == nullptr && "Texture is not null! Don't move a texture into an initalized texture." );
    std::swap( _sdlSurfacePtr, aOther._sdlSurfacePtr );
    std::swap( _sdlTexturePtr, aOther._sdlTexturePtr );

    return *this;
}

// ------------------------------------------------------------

Uint16 ost::STexture::GetWidth() const
{
    if ( _sdlTexturePtr == nullptr )
    {
        return 0u;
    }
    return static_cast<Uint16>( _sdlTexturePtr->w );
}

// ------------------------------------------------------------

Uint16 ost::STexture::GetHeight() const
{
    if ( _sdlTexturePtr == nullptr )
    {
        return 0u;
    }
    return static_cast<Uint16>( _sdlTexturePtr->h );
}

// ------------------------------------------------------------

void ost::STexture::LoadFromFile( const std::string& aPath, CRenderer& aRenderer )
{
    _sdlSurfacePtr = SDL_LoadBMP( aPath.c_str() );
    _sdlTexturePtr = SDL_CreateTextureFromSurface( aRenderer.GetRendererPtr().Get<SDL_Renderer>(), _sdlSurfacePtr );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
