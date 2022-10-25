// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#include "Common/Public/Debugging/Logging/LoggerBase.h"

using namespace ost;

CLoggerBase::CLoggerBase(const std::string instanceName)
	: InstanceName(instanceName)
{
}

const std::string& ost::CLoggerBase::GetInstanceName() const
{
	return InstanceName;
}

