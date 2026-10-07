// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Data/TextureCPUData.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class ImageLoader
    {
    public:
        void Load(const std::string& path, TextureCPUData& into) const; 
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------