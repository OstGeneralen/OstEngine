// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LoggerApi.h"
#include "OstLog/LogMessage.h"
#include <string>

// ------------------------------------------------------------

#define OSTLOG_LOG_INSTANCE( LoggerName ) ost::log::CLogInstance LoggerName( #LoggerName )

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class LOGGER_API CLogInstance
		{
		public:
			CLogInstance(std::string instanceName);

			void EndScope();

			template<typename ... TFmt>
			void LogScoped(ELogLevel lvl, std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
			{
				SLogMessage msg;
				msg.Level = lvl;
				msg.LoggerName = _instanceName;
				msg.Timestamp = std::chrono::system_clock::now();
				msg.Source = std::source_location::current();
				msg.MessageFormatter = [fmtStr, ...args = std::forward<TFmt>(fmtArgs)]() mutable {
					return std::format(fmtStr, std::forward<TFmt>(args)...);
					};

				BeginLogScope(msg);
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
			void BeginLogScope(const SLogMessage& scopeRootMsg);

			const std::string _instanceName;
			SLogMessage _currentMessage;
			SLogMessage* _currentMessageScope{ nullptr };
		};

	}
}

// ------------------------------------------------------------