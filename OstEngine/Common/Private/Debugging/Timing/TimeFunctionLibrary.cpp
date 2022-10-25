// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#include "Common/Public/Debugging/Timing/TimeFunctionLibrary.h"
#include <chrono>
#include <format>

using namespace ost;

std::string debugtime::GetNowAsFormattedString(bool includeDate)
{
	auto now = std::chrono::system_clock::now();

	if (includeDate)
	{
		return std::format("{0:%Y-%m-%d %H:%M:%S}", now);
	}

	return std::format("{0:%H:%M:%S}", now);
}