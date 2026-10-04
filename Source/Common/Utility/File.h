// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Memory/Blob.h"
#include <string>

// ------------------------------------------------------------

namespace ost
{
    namespace FileUtility
    {
        extern Blob ReadFileToBlob( const std::string& path );
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------