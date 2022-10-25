#pragma once
#include <string>
#include <format>

namespace ost
{
	namespace stringhelpers
	{
		extern std::string WstrToStr(const std::wstring& wstr);
		extern std::wstring StrToWstr(const std::string& str);

		template<typename ... TArgs>
		std::string FormatString(std::string_view fmt, TArgs&&... args)
		{
			return std::move(std::vformat(fmt, std::make_format_args(args...)));
		}
	}
}