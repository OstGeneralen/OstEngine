// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Game/GameInstance.h>
#include <OstEngine/Game/GameModuleInternal.h>
#include <OstEngine/Application/CommandLine/CommandLineParser.h>
#include <OstEngine/Application/CommandLine/CommandLineArgs.h>

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
    ost::CCommandLineParser cmdParser = ost::CCommandLineParser(argv, argc);

    std::cout << "Attempting to load " <<  GAME_MODULE_DLL_NAME << std::endl;

    std::cout << "Running with config" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Width: " << ost::command_line::ReadFromParser(ost::command_line::WinWidth, cmdParser) << std::endl;
    std::cout << "Height: " << ost::command_line::ReadFromParser(ost::command_line::WinHeight, cmdParser) << std::endl;

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



