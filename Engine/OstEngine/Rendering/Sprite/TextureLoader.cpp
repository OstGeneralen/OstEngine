#include "TextureLoader.h"

// ------------------------------------------------------------

ost::CTextureLoader::CTextureLoader( CRenderer& aRenderer )
    : _renderer{aRenderer}
    , _textureBank{}
{
}

// ------------------------------------------------------------

ost::STexture* ost::CTextureLoader::GetTexture( const std::string& aTextureName )
{
    auto fIterator = _textureBank.find( aTextureName );
    if (fIterator == _textureBank.end())
    {
        return &LoadTexture( aTextureName );
    }
    return &( fIterator->second );
}

// ------------------------------------------------------------

ost::STexture& ost::CTextureLoader::LoadTexture( const std::string& aTextureName )
{
    _textureBank[aTextureName] = std::move( STexture( aTextureName, _renderer ) );
    return _textureBank[aTextureName];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
