#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Rendering/Sprite/SpriteData.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// ------------------------------------------------------------

extern ost::IGame* GameMain();

// ------------------------------------------------------------

int main( int aArgCount, char* aArgs[] )
{
    ost::CEngine::InitializeEngine();

    ost::CEngine::Instance()->Run( *GameMain() );

    ost::CEngine::ShutdownEngine();
    return 0;
}

// ------------------------------------------------------------
