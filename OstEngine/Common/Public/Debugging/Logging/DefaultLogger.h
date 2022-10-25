// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#pragma once
#include <Common/Public/Debugging/Logging/LoggerBase.h>

namespace ost
{
	class CDefaultLogger : public CLoggerBase
	{
	public:
		CDefaultLogger(const std::string instanceName) : CLoggerBase(instanceName)
		{}

		void LogString(ELogVerbosity verbosity, std::string msg) override;

	private:
		void PrintInfo(const std::string& infoText);
		
	};
}