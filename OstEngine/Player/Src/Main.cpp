// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Game/GameInstance.h>
#include <OstEngine/Game/GameModuleInternal.h>
#include <OstEngine/Application/Config/CommandLineParser.h>
#include <OstEngine/Application/Config/ConfigValues.h>

#if APP_WIN32
#include <Windows.h>

int CALLBACK WinMain(_In_ HINSTANCE aInst, _In_opt_ HINSTANCE pInst, _In_ LPSTR cmd, _In_ int cmdShw)
{
    return 0;
}
#else
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
    ost::CCommandLineParser cmdParser = ost::CCommandLineParser(argv, argc);

    std::cout << "Parsed " << cmdParser.GetParsedValues().size() << " cmd args" << std::endl;

    ostengine_internal::CGameModuleLoader moduleLoader;

    const std::string gameModuleName = cmdParser.ReadArg(ost::cfg_val::cmdArg_GameModule);
    if (moduleLoader.LoadModule(gameModuleName.c_str()) == ostengine_internal::ModuleLoaderStatus_Success)
    {
        ost::IGameInstance* moduleInstance = moduleLoader.CreateGameModuleInstance();
        moduleInstance->Run();
        moduleLoader.ReleaseGameModuleInstance(&moduleInstance);
        moduleLoader.ReleaseModule();
    }


    return 0;
}
#endif



