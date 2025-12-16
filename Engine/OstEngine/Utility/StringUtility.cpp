#include "StringUtility.h"
#include <sstream>

// ------------------------------------------------------------

std::string ost::stringUtils::WStringToString( const std::wstring& aWStr )
{
    std::stringstream buildStream;
    for (auto c : aWStr)
    {
        buildStream << static_cast<char>( c );
    }

    return buildStream.str();
}

// ------------------------------------------------------------