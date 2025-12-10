#pragma once
#include <OstEngine/Rendering/Window.h>
#include <OstEngine/Rendering/Renderer.h>
#include <OstEngine/Rendering/Sprite/TextureLoader.h>

namespace ost
{
    class CEngine
    {
        friend class COstEngineApp;
    public:
        static CEngine* Instance();

    public:
        void InitializeRendering( CWindow& appWindow );
        void Deinitialize();


        CRenderer& GetRenderer();
        CTextureLoader& GetTextureLoader();
    private:
        CRenderer _renderer;
        CTextureLoader _textureLoader;

    private:
        CEngine();
        static CEngine* _instancePtr;
    };
} // namespace ost