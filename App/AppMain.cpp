#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <OstEngine/Application/AppBase.h>

// ------------------------------------------------------------

class CApp : public ost::COstEngineApp
{
    ost::Vector2i WindowDimensions() const override
    {
        return { 800, 600 };
    }

    std::string WindowTitle() const override
    {
        return "Application";
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
