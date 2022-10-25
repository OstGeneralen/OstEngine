// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once

#include <format>
#include <string>

namespace ost
{
	namespace stringhelpers
	{
		extern std::string WstrToStr( const std::wstring& wstr );
		extern std::wstring StrToWstr( const std::string& str );

		template < typename... TArgs >
		std::string FormatString( std::string_view fmt, TArgs&&... args )
		{
			return std::move( std::vformat( fmt, std::make_format_args( args... ) ) );
		}
	} // namespace stringhelpers
} // namespace ost