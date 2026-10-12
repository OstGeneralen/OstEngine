// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <codecvt>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    namespace StringUtility
    {
        // string to wstring (assuming utf16 wstring and utf8 string)
        inline std::wstring Utf8ToUtf16(const std::string& utf8)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(utf8);
        }

        // wstring to string (assuming utf16 wstring and utf8 string)
        inline std::string Utf16ToUtf8(const std::wstring& utf16)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.to_bytes(utf16);
        }
    } // namespace StringUtility
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------