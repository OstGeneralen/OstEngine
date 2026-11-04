// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Memory/Blob.h"
#include "Container/List.h"
#include <string>

// ------------------------------------------------------------

namespace ost
{
    namespace FileUtility
    {
        extern Blob ReadFileToBlob( const std::string& path );
        extern char* ReadFileToCharArray( const std::string& path, SizeType& outSize );
        extern std::string ReadFileToString( const std::string& path );
        extern List<Uint8> ReadFileToByteList( const std::string& path );
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------