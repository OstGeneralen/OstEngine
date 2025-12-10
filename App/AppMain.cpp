#include <OstEngine/Application/AppBase.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Rendering/Sprite/SpriteData.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// ------------------------------------------------------------

class CApp : public ost::IApplication
{
    ost::SSprite mySprite;

    void Load() override
    {
        ost::CEngine& engine = *ost::CEngine::Instance();
        ost::CTextureLoader& textureLoader = engine.GetTextureLoader();

        mySprite.Create(*(textureLoader.GetTexture("Assets/Textures/TestTexture.bmp")));
    }
    
    void Update() override
    {
    }
    
    void Render() override
    {
        ost::CEngine& engine = *ost::CEngine::Instance();
        ost::CRenderer& renderer = engine.GetRenderer();
        renderer.DrawSprite( mySprite );
    }
};

// ------------------------------------------------------------

int main( int aArgCount, char* aArgs[] )
{
    ost::CEngine::InitializeEngine();

    CApp app;
    ost::CEngine::Instance()->Run( app );


    ost::CEngine::ShutdownEngine();
    return 0;
}

// ------------------------------------------------------------
