// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Configuration/AppCmdArgs.h>

// ------------------------------------------------------------

ost::SAppCmdArgs::SAppCmdArgs(char* argv[], int argc)
{
	_args.reserve(argc);

	for (int i = 0; i < argc; ++i)
	{
		_args.emplace_back(argv[i]);
	}
}

// ------------------------------------------------------------

bool ost::SAppCmdArgs::TryRead(const SCmdArg& arg, std::string_view& outValue) const
{
	for (uint64 i = 0; i < _args.size(); ++i)
	{
		const bool nextArgIsValue = i < _args.size() - 1 && _args[i + 1][0] != '-';
		if (!nextArgIsValue)
		{
			continue;
		}

		const char* argStr = _args[i].data();
		const char* argFull = arg.Command_Full.data();
		const char* argShort = arg.Command_Short.data();
		const bool match = strcmp(argStr, argFull) == 0 || strcmp(argStr, argShort) == 0;

		if (match)
		{
			outValue = _args[i + 1];
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------

bool ost::SAppCmdArgs::TryRead_Int(const SCmdArg& arg, int32& outValue) const
{
	std::string_view valStr;
	if (TryRead(arg, valStr))
	{
		try 
		{
			outValue = std::stoi(valStr.data());
			return true;
		}
		catch (std::exception e)
		{
			return false;
		}
	}
	return false;
}

// ------------------------------------------------------------

bool ost::SAppCmdArgs::TryRead_Flt(const SCmdArg& arg, float32& outValue) const
{
	std::string_view valStr;
	if (TryRead(arg, valStr))
	{
		try
		{
			outValue = std::stof(valStr.data());
			return true;
		}
		catch (std::exception e)
		{
			return false;
		}
	}
	return false;
}

// ------------------------------------------------------------

bool ost::SAppCmdArgs::TryRead_Str(const SCmdArg& arg, std::string& outValue) const
{
	std::string_view valStrView;
	if (TryRead(arg, valStrView))
	{
		outValue = valStrView.data();
		return true;
	}
	return false;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------