// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <filesystem>
#include <Utility/Delegate.h>

// ------------------------------------------------------------

namespace ost
{
    class FileSystem
    {
    public:
        Delegate<const std::filesystem::path&> projectPathChanged;

        void SetProjectAssetPath( const std::filesystem::path& p );
        

    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------