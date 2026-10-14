// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Configuration/RuntimeConfig.h"

#include <fstream>

#include <nlohmann/json.hpp>

using namespace ost;
using namespace nlohmann;

// ------------------------------------------------------------

// ------------------------------------------------------------

void ost::RuntimeConfig::LoadFromFile(const std::string& filePath)
{
    json configRoot;
    {
        std::ifstream rdStream(filePath);
        configRoot << rdStream;
    }

    // Load paths data
    assets.LoadFromJson(configRoot["paths"]);
    window.LoadFromJson(configRoot["window"]);
    rendering.LoadFromJson(configRoot["rendering"]);
}

// ------------------------------------------------------------

void ost::AssetPathConfig::LoadFromJson(const nlohmann::json& j)
{
    rootPath = j["rootDir"].get<std::string>();
    prefix = j["prefix"].get<std::string>();
}

void ost::AssetsConfig::LoadFromJson(const nlohmann::json& j)
{
    game.LoadFromJson(j["assets"]);
    engine.LoadFromJson(j["engine"]);
}

void ost::WindowConfig::LoadFromJson(const nlohmann::json& j)
{
    title = j["title"].get<std::string>();
    fullscreen = j["fullscreen"].get<bool>();

    const auto r = j["resolution"];
    resolution = {r[0].get<Uint32>(), r[1].get<Uint32>()};
}

void ost::RenderConfig::LoadFromJson(const nlohmann::json& j)
{
    const auto s = j["renderScale"];

    renderScale = {s[0].get<Float32>(), s[1].get<Float32>()};

    const std::string rendererStr = j["renderer"];
    if (rendererStr == "deferred")
    {
        renderer = ERendererType::Deferred;
    }
    else if (rendererStr == "forward")
    {
        renderer = ERendererType::Forward;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------