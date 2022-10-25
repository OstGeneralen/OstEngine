// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once

#include "Common/Public/Debugging/Logging/ConsoleColors.h"
#include "Common/Public/Debugging/Logging/LoggingFunctionLibrary.h"
#include "Common/Public/Debugging/Logging/Verbosity.h"
#include "Common/Public/String/StringHelperLibrary.h"
#include <string_view>

#include <string>

namespace ost
{
	class CLoggerBase
	{
	public:
		template < typename... FmtArgs >
		void Log( ELogVerbosity verbosity, std::string_view logMsg, FmtArgs&&... fmtArgs )
		{
			LogString( verbosity, stringhelpers::FormatString( logMsg, fmtArgs... ) );
		}

	public: // Overrides
		virtual void LogString( ELogVerbosity verbosity, std::string message ) = 0;

	public: // Base type
		CLoggerBase( const std::string instanceName );
		const std::string& GetInstanceName() const;

	private:
		std::string InstanceName;
	};
} // namespace ost