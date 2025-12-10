#pragma once
#include <OstEngine/Math/Color.h>
#include <OstEngine/Utility/UntypedPointer.h>
#include <OstEngine/Rendering/Sprite/SpriteData.h>
#include <OstEngine/Math/Color.h>

struct SDL_Renderer;

namespace ost
{
    class CWindow;

	class CRenderer
	{
    public:
        void Initialize(CWindow& aWindow, const SColor& clearColor);
        void Deinitialize();

        void BeginFrame();
        void EndFrame();

        void DrawSprite( SSprite& aSprite );

        SUntypedPtr GetRendererPtr();
    private:
        SColor _clearColor;
        SDL_Renderer* _rendererPtr;

	};
}