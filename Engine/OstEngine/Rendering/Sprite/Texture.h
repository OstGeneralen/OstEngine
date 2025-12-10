#pragma once
#include <OstEngine/Types.h>
#include <string>

struct SDL_Surface;
struct SDL_Texture;

namespace ost
{
    class CRenderer;

	struct STexture
	{
        friend struct SSprite;

    public:
        STexture();
        STexture( const std::string& aPath, CRenderer& aRenderer );
        STexture( STexture&& aOther ) noexcept;
        ~STexture();

        STexture& operator=( STexture&& aOther ) noexcept;

        STexture( const STexture& ) = delete;
        STexture& operator=( const STexture& ) = delete;

        void LoadFromFile( const std::string& aPath, CRenderer& aRenderer );

        Uint16 GetWidth() const;
        Uint16 GetHeight() const;
    private:
        SDL_Surface* _sdlSurfacePtr;
        SDL_Texture* _sdlTexturePtr;
	};
}