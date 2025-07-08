// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string_view>
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Utility/StringHashing.h>

// ------------------------------------------------------------

#define CMD_ARG( VarName, CmdFull, CmdShort, Desc ) constexpr ost::SCmdArg VarName { CmdFull, CmdShort, Desc };
#define CMD_ARG_S(VarName, CmdFull, CmdShort, Desc) static CMD_ARG(VarName, CmdFull, CmdShort, Desc) 

#define CMD_VAR( Var ) Var
#define CMD_FULL( Cmd ) "-"#Cmd
#define CMD_SHORT(Cmd) "-"#Cmd
#define CMD_DESC( Desc ) Desc


// ------------------------------------------------------------

namespace ost
{
	struct SCmdArg
	{
		constexpr SCmdArg(std::string_view f, std::string_view s, std::string_view d)
			: Command_Full(f)
			, Command_Short(s)
			, Desc(d)
			, CommandHash(string_hash::HashString_64(f))
		{
		}

		std::string_view Command_Full;
		std::string_view Command_Short;
		std::string_view Desc;
		uint64 CommandHash;
	};
}

// ------------------------------------------------------------

namespace std
{
	template<>
	struct hash<ost::SCmdArg>
	{
		std::size_t operator()(const ost::SCmdArg& a) const noexcept
		{
			return a.CommandHash;
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------