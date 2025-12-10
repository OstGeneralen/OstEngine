#include "Renderer.h"

#include "Window.h"

#include <SDL3/SDL.h>

void ost::CRenderer::Initialize( CWindow& aWindow, const SColor& clearColor )
{
    _rendererPtr = SDL_CreateRenderer( aWindow.GetWindowPointer().Get<SDL_Window>(), 0 );
    _clearColor = clearColor;
}

void ost::CRenderer::Deinitialize()
{
    if ( _rendererPtr != nullptr )
    {
        SDL_DestroyRenderer( _rendererPtr );
    }
}

void ost::CRenderer::BeginFrame()
{
    SDL_SetRenderDrawColor( _rendererPtr, _clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A );
    SDL_RenderClear( _rendererPtr );
}

void ost::CRenderer::EndFrame()
{
    SDL_RenderPresent( _rendererPtr );
}

void ost::CRenderer::DrawSprite( SSprite& aSprite )
{
    SDL_SetRenderDrawColor( _rendererPtr, aSprite.DrawColor.R, aSprite.DrawColor.G, aSprite.DrawColor.B,
                            aSprite.DrawColor.A );
    const SDL_FRect srcRect = aSprite.SourceRect.ToSDLRect();
    const SDL_FRect dstRect = Rectf( aSprite.Location, aSprite.SourceRect.Dimensions ).ToSDLRect();
    SDL_RenderTexture( _rendererPtr, aSprite.BackendTexturePtr.Get<SDL_Texture>(), &srcRect, &dstRect );
}

ost::SUntypedPtr ost::CRenderer::GetRendererPtr()
{
    return SUntypedPtr( _rendererPtr );
}
