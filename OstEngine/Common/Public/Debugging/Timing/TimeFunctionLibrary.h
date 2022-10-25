// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include <string>

namespace ost
{
	namespace debugtime // This namespace is only for debugging purposes, not for delta time or other app sensitive timing
	{
		extern std::string GetNowAsFormattedString( bool includeDate );
	}
} // namespace ost
