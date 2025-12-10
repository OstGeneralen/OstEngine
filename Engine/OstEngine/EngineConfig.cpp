#include "EngineConfig.h"

#include <fstream>
#include <json.hpp>

using namespace nlohmann;

void ost::SEngineConfig::LoadFromFile( const std::string& configPath )
{
    try
    {
        std::ifstream readStream( configPath );

        json configFileRoot = json::parse( readStream );
        readStream.close();

        WindowTitle = configFileRoot["window_title"].get<std::string>();
        Windowed = configFileRoot["windowed_mode"].get<bool>();

        json resCfg = configFileRoot["resolution"];
        Resolution = Vector2i{ resCfg["w"], resCfg["h"] };

        json clrCfg = configFileRoot["clear_color"];
        ClearColor = SColor( clrCfg["r"].get<float>(), clrCfg["g"].get<float>(), clrCfg["b"].get<float>(), 1.0f );
    }
    catch (std::exception e)
    {
        InitDefault();
    }
}

void ost::SEngineConfig::InitDefault()
{
    WindowTitle = "OstEngine Window";
    Windowed = true;
    Resolution = { 800, 800 };
    ClearColor = 0xAA00FFFF;
}
