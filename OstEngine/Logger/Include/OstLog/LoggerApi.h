// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#if LOGGER_DLL_BUILD
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class ILogger;
	}
}

extern "C" LOGGER_API ost::log::ILogger& GetLogger();


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------