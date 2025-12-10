#pragma once
#include <OstEngine/Rendering/Window.h>
#include <OstEngine/Rendering/Renderer.h>
#include <OstEngine/Rendering/Sprite/TextureLoader.h>
#include <OstEngine/Application/AppBase.h>

namespace ost
{
    class CEngine
    {
    public:
        static CEngine* Instance();
        static void InitializeEngine();
        static void ShutdownEngine();

    public:
        void Run(IApplication& aAppInterface);

        CRenderer& GetRenderer();
        CTextureLoader& GetTextureLoader();
    private:
        void Initialize();
        void Deinitialize();

        CWindow _window;
        CRenderer _renderer;
        CTextureLoader _textureLoader;
        IApplication* _appPtr;

    private:
        CEngine();
        static CEngine* _instancePtr;
    };
} // namespace ost