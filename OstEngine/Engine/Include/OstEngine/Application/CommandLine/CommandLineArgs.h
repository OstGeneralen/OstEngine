// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Application/CommandLine/CommandLineParser.h"

// ------------------------------------------------------------

namespace ost
{
	namespace command_line
	{
		template<typename T>
		struct TCommandLineValue
		{
			TCommandLineValue(const std::string vn, T dv)
				: ValueName{ vn }
				, DefaultValue{ dv }
			{
			}
			const std::string ValueName;
			const T DefaultValue;
		};

		template<typename T> T ReadFromParser(const TCommandLineValue<T>& v, CCommandLineParser& parser) { static_assert(false); }
		template<> float ReadFromParser<float>(const TCommandLineValue<float>& v, CCommandLineParser& parser)
		{
			SCommandLineValue cv;
			if (parser.TryGetCommandLine(v.ValueName, cv))
			{
				return cv.ReadAsFloat(v.DefaultValue);
			}
			return v.DefaultValue;
		}
		template<> int ReadFromParser<int>(const TCommandLineValue<int>& v, CCommandLineParser& parser)
		{
			SCommandLineValue cv;
			if (parser.TryGetCommandLine(v.ValueName, cv))
			{
				return cv.ReadAsInt(v.DefaultValue);
			}
			return v.DefaultValue;
		}
		template<> std::string ReadFromParser<std::string>(const TCommandLineValue<std::string>& v, CCommandLineParser& parser)
		{
			SCommandLineValue cv;
			if (parser.TryGetCommandLine(v.ValueName, cv))
			{
				return cv.ReadAsString();
			}
			return v.DefaultValue;
		}


		
		const static TCommandLineValue<int> WinWidth{ "-w", 1920 };
		const static TCommandLineValue<int> WinHeight{ "-h", 1080 };
	}

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------