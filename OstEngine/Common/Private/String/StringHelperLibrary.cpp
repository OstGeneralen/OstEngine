#include "Common/Public/String/StringHelperLibrary.h"

std::string ost::stringhelpers::WstrToStr(const std::wstring& wstr)
{
	return std::move(std::string(wstr.begin(), wstr.end()));
}

std::wstring ost::stringhelpers::StrToWstr(const std::string& str)
{
	return std::move(std::wstring(str.begin(), str.end()));
}