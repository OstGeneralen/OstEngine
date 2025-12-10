#pragma once
#include <OstEngine/Rendering/Sprite/Texture.h>
#include <map>

namespace ost
{
    class CRenderer;

	class CTextureLoader
	{
    public:
        CTextureLoader( CRenderer& aRenderer );
        STexture* GetTexture( const std::string& aTextureName );
    private:
        STexture& LoadTexture( const std::string& aTextureName );

        CRenderer& _renderer;
        std::map<std::string, STexture> _textureBank;  
	};
}