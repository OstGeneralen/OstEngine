// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/Logging/LoggerApi.h"
#include "OstLog/Logging/LogMessage.h"
#include "OstLog/Logging/LogScope.h"
#include <string>

// ------------------------------------------------------------

#define OSTLOG_LOG_INSTANCE( LoggerName ) ost::log::CLogInstance LoggerName( #LoggerName )

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		struct SLogScope;

		class LOGGER_API CLogInstance
		{
			friend SLogScope;

		public:
			CLogInstance(std::string instanceName);

			template<typename ... TFmt>
			SLogScope ScopedLog(ELogLevel lvl, std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
			{
				SLogMessage msg;
				msg.Level = lvl;
				msg.LoggerName = _instanceName;
				msg.Timestamp = std::chrono::system_clock::now();
				msg.Source = std::source_location::current();
				msg.MessageFormatter = [fmtStr, ...args = std::forward<TFmt>(fmtArgs)]() mutable {
					return std::format(fmtStr, std::forward<TFmt>(args)...);
					};
				return std::move(SLogScope(msg, this));
			}

			template<typename ... TFmt>
			void Log(ELogLevel lvl, std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
			{
				SLogMessage msg;
				msg.Level = lvl;
				msg.LoggerName = _instanceName;
				msg.Timestamp = std::chrono::system_clock::now();
				msg.Source = std::source_location::current();
				msg.MessageFormatter = [fmtStr, ...args = std::forward<TFmt>(fmtArgs)]() mutable {
					return std::format(fmtStr, std::forward<TFmt>(args)...);
					};
				Log(msg);
			}

		private:
			void Log(const SLogMessage& msg);
			const std::string _instanceName;
			SLogScope* _activeScope;
		};

	}
}

// ------------------------------------------------------------