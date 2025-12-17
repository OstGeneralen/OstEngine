#pragma once
#include <string>

namespace ost
{
	namespace stringUtils
	{
        extern std::string WStringToString( const std::wstring& aWStr );
        extern std::wstring StringToWString( const std::string& aStr );
	}
}