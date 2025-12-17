#pragma once
#include <OstEngine/Math/Color.h>
#include <OstEngine/Math/Vectors.h>
#include <string>

namespace ost
{
    struct SEngineConfig
    {
        std::string WindowTitle;
        bool Windowed = true;
        Vector2i Resolution;
        SColor ClearColor;
        
        void LoadFromFile( const std::string& configPath );
        void InitDefault();
    };
} // namespace ost