// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Configuration/CmdArg.h>

#include <vector>
#include <string_view>
#include <string>

// ------------------------------------------------------------

namespace ost
{
	struct SAppCmdArgs
	{
	public:
		SAppCmdArgs(char* argv[], int argc);

		template<typename T> bool TryRead(const SCmdArg& arg, T& outVal) const { return false; }
		template<> bool TryRead<int32>(const SCmdArg& arg, int32& outVal) const { return TryRead_Int(arg, outVal); }
		template<> bool TryRead<float32>(const SCmdArg& arg, float32& outVal) const { return TryRead_Flt(arg, outVal); }
		template<> bool TryRead<std::string>(const SCmdArg& arg, std::string& outVal) const { return TryRead_Str(arg, outVal); }

		template<typename T> T ReadWithDefault(const SCmdArg& arg, const T& def) const { return T(); }
		template<> int32 ReadWithDefault<int32>(const SCmdArg& arg, const int32& def) const 
		{
			int32 readVal = def;
			TryRead<int32>(arg, readVal);
			return readVal;
		}
		template<> float32 ReadWithDefault<float32>(const SCmdArg& arg, const float32& def) const
		{
			float32 readVal = def;
			TryRead<float32>(arg, readVal);
			return readVal;
		}
		template<> std::string ReadWithDefault<std::string>(const SCmdArg& arg, const std::string& def) const
		{
			std::string readVal = def;
			TryRead<std::string>(arg, readVal);
			return readVal;
		}
	private:
		bool TryRead(const SCmdArg& arg, std::string_view& outValue) const;
		bool TryRead_Int(const SCmdArg& arg, int32& outValue) const;
		bool TryRead_Flt(const SCmdArg& arg, float32& outValue) const;
		bool TryRead_Str(const SCmdArg& arg, std::string& outValue) const;

		std::vector<std::string_view> _args;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------