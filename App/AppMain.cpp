#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>
#include <Windows.h>

// ------------------------------------------------------------

extern ost::IGame* GameMain();

// ------------------------------------------------------------

int WINAPI wWinMain( _In_ HINSTANCE aInstance, _In_opt_ HINSTANCE aPrevInstance, _In_ PWSTR aCmd, _In_ Int32 aCmdShow )
{
    aPrevInstance;
    aCmdShow;
    aCmd;

    ost::IGame& gameInstance = *GameMain();
    ost::CEngine::InitializeEngine(aInstance);
    
    ost::CEngine::Instance()->Run( gameInstance );
    
    ost::CEngine::ShutdownEngine();
    return 0;
}

// ------------------------------------------------------------
