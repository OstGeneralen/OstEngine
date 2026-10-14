// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <string>

#include <GraphicsEngine/IGraphicsEngine.h>
#include <Math/Vector2.h>
#include <nlohmann/json_fwd.hpp>

// ------------------------------------------------------------

namespace ost
{
    struct AssetPathConfig
    {
        void LoadFromJson(const nlohmann::json& j);

        std::string rootPath = "";
        std::string prefix = "";
    };

    struct AssetsConfig
    {
        void LoadFromJson(const nlohmann::json& j);

        AssetPathConfig game;
        AssetPathConfig engine;
    };

    struct WindowConfig
    {
        void LoadFromJson(const nlohmann::json& j);

        std::string title = "Ost Window";
        Vector2u resolution = {1600, 900};
        bool fullscreen = false;
    };

    struct RenderConfig
    {
        void LoadFromJson(const nlohmann::json& j);

        Vector2f renderScale = {1, 1};
        ERendererType renderer = ERendererType::Forward;
    };

    struct RuntimeConfig
    {
        void LoadFromFile(const std::string& filePath);

        AssetsConfig assets;
        WindowConfig window;
        RenderConfig rendering;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------