#pragma once
#include <OstEngine/Math/Color.h>
#include <OstEngine/Utility/UntypedPointer.h>
#include <OstEngine/Rendering/Sprite/SpriteData.h>

struct SDL_Renderer;

namespace ost
{
    class CWindow;

	class CRenderer
	{
    public:
        void Initialize(CWindow& aWindow);
        void Deinitialize();

        void BeginFrame(const SColor& aColor);
        void EndFrame();

        void DrawSprite( SSprite& aSprite );

        SUntypedPtr GetRendererPtr();
    private:
        SDL_Renderer* _rendererPtr;
	};
}