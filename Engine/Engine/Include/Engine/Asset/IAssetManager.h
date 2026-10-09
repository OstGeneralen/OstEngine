// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <filesystem>

#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class IAssetManager
    {
    public:
        virtual TextureHandle LoadTextureFromFile(const std::filesystem::path& path) = 0;
        virtual ModelHandle LoadModelFromFile(const std::filesystem::path& path) = 0;

        virtual void Release( TextureHandle h ) = 0;
        virtual void Release( ModelHandle h ) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------