#include "SpriteData.h"

void ost::SSprite::Create( STexture& aTexture )
{
    BackendTexturePtr = aTexture._sdlTexturePtr;
    SourceRect = Rectf( { 0.0f, 0.0f },
                        { static_cast<Float32>( aTexture.GetWidth() ), static_cast<Float32>( aTexture.GetHeight() ) } );
    Location = Vector2f{};
    DrawColor = Color::White;
}

void ost::SSprite::Create( STexture& aTexture, const Rectf& aRect )
{
    Create( aTexture );
    SourceRect = aRect;
}
