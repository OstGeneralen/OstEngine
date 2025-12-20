#pragma once
#include <string>

// ------------------------------------------------------------

namespace ost
{
    namespace util
    {
        namespace string
        {
            extern std::string WStringToString( const std::wstring& aWStr );
            extern std::wstring StringToWString( const std::string& aStr );
        }
    } // namespace util
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------