#include "OstEngine/Common/Utility/StringUtility.h"

#include <sstream>

// ------------------------------------------------------------

std::string ost::util::string::WStringToString( const std::wstring& aWStr )
{
    std::stringstream buildStream;
    for ( auto c : aWStr )
    {
        buildStream << static_cast<char>( c );
    }

    return buildStream.str();
}

// ------------------------------------------------------------

std::wstring ost::util::string::StringToWString( const std::string& aStr )
{
    return std::wstring( aStr.begin(), aStr.end() );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------