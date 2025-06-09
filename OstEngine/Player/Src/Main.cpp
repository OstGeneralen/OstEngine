// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Game/GameInstance.h>
#include <OstEngine/Game/GameModuleInternal.h>
#include <OstEngine/Application/Config/CommandLineParser.h>
#include <OstEngine/Application/Config/ConfigFileParser.h>
#include <OstEngine/Application/Config/ConfigValues.h>
#include <OstEngine/Application/Window/Window.h>

#if APP_WIN32
#include <Windows.h>

int CALLBACK WinMain(_In_ HINSTANCE aInst, _In_opt_ HINSTANCE pInst, _In_ LPSTR cmd, _In_ int cmdShw)
{
    // Parse command line args and the config file
    ost::CCommandLineParser cmdParser{ cmd };
    ost::CConfigFileParser cfgParser;
    cfgParser.ReadConfigFile("OstEngine.cfg");

    // Try to load the game module
    ost::IGameInstance* gameInstance = nullptr;
    std::string gameModuleName = cfgParser.ReadValue(ost::config_GameModule);
    ostengine_internal::CGameModuleLoader moduleLoader;
    if (moduleLoader.LoadModule(gameModuleName.c_str()) == ostengine_internal::ModuleLoaderStatus_Success)
    {
        gameInstance = moduleLoader.CreateGameModuleInstance();
    }
    else 
    { 
        return -1; 
    }

    // Create the application window
    ost::SWindowSettings winSettings{};
    winSettings.Width = cfgParser.ContainsConfig(ost::config_WinWidth) ? cfgParser.ReadValue(ost::config_WinHeight) : cmdParser.ReadArg(ost::config_WinWidth);
    winSettings.Height = cfgParser.ContainsConfig(ost::config_WinHeight) ? cfgParser.ReadValue(ost::config_WinHeight) : cmdParser.ReadArg(ost::config_WinHeight);
    winSettings.Title = gameInstance->GameTitle();
    winSettings.InstanceInfo = aInst;
    winSettings.InstanceFlags = cmdShw;

    ost::CWindow appWindow;
    appWindow.Create(winSettings);


    while (appWindow.IsOpen())
    {
        appWindow.ProcessEvents();
    }


    return 0;
}
#else
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
    ost::CCommandLineParser cmdParser = ost::CCommandLineParser(argv, argc);
    ost::CConfigFileParser cfgParser;
    cfgParser.ReadConfigFile("OstEngine.cfg");

    ostengine_internal::CGameModuleLoader moduleLoader;

    const bool hasConfigModuleName = cfgParser.ContainsConfig(ost::config_GameModule);
    const std::string gameModuleName = hasConfigModuleName ? cfgParser.ReadValue(ost::config_GameModule) : cmdParser.ReadArg(ost::config_GameModule);
    if (moduleLoader.LoadModule(gameModuleName.c_str()) == ostengine_internal::ModuleLoaderStatus_Success)
    {
        ost::IGameInstance* moduleInstance = moduleLoader.CreateGameModuleInstance();
        moduleInstance->Run();
        moduleLoader.ReleaseGameModuleInstance(&moduleInstance);
        moduleLoader.ReleaseModule();
    }


    if (!hasConfigModuleName)
    {
        cfgParser.SetConfigValue(ost::config_GameModule, gameModuleName);
    }

    cfgParser.WriteConfigFile("OstEngine.cfg");

    return 0;
}
#endif



