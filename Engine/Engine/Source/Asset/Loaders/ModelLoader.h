// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Resources/ModelCPUData.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class ModelLoader
    {
    public:
        void Load(const std::string& path, ModelCPUData& into);
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------