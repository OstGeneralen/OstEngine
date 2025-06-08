// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Game/GameInstance.h>
#include <OstEngine/Game/GameModuleInternal.h>

#if APP_WIN32
#include <Windows.h>

int CALLBACK WinMain(_In_ HINSTANCE aInst, _In_opt_ HINSTANCE pInst, _In_ LPSTR cmd, _In_ int cmdShw)
{
    return 0;
}
#else
#include <iostream>

int main(int argc, char* argv[])
{

    std::cout << "Attempting to load " <<  GAME_MODULE_DLL_NAME << std::endl;

    ostengine_internal::CGameModuleLoader moduleLoader;

    if (moduleLoader.LoadModule(GAME_MODULE_DLL_NAME) == ostengine_internal::ModuleLoaderStatus_Success)
    {
        ost::IGameInstance* moduleInstance = moduleLoader.CreateGameModuleInstance();
        moduleInstance->Run();
        moduleLoader.ReleaseGameModuleInstance(&moduleInstance);
        moduleLoader.ReleaseModule();
    }


    return 0;
}
#endif



