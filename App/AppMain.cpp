#include <OstEngine/Application/AppBase.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Rendering/Sprite/SpriteData.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// ------------------------------------------------------------

class CApp : public ost::COstEngineApp
{
    ost::SSprite sprite;
    float totalTime = 0.0f;

    ost::Vector2i WindowDimensions() const override
    {
        return { 800, 600 };
    }

    std::string WindowTitle() const override
    {
        return "Application";
    }

    void Init_PostEngine( ost::CEngine& aEngine ) override
    {
        sprite.Create( *( aEngine.GetTextureLoader().GetTexture( "Assets/Textures/TestTexture.bmp" ) ) );
        sprite.Location = { 100, 100 };
        sprite.DrawColor = ost::Color::Red;
    }

    void Tick() override
    {
        totalTime += 0.00001f;

        sprite.Location += { totalTime, totalTime };

        ost::CRenderer& renderer = ost::CEngine::Instance()->GetRenderer();
        renderer.DrawSprite( sprite );
    }
};

// ------------------------------------------------------------

int main( int aArgCount, char* aArgs[] )
{
    CApp app;
    app.Init();
    app.Run();
    app.DeInit();
    return 0;
}

// ------------------------------------------------------------
