// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LoggerApi.h"
#include "OstLog/LogMessage.h"
#include <string>

// ------------------------------------------------------------

#define CREATE_LOG_INSTANCE( LoggerName ) ost::log::CLogInstance LoggerName( #LoggerName )

#define LOG_TRACE( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Trace, Msg, __VA_ARGS__ )
#define LOG_DEBUG( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Debug, Msg, __VA_ARGS__ )
#define LOG_INFO( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Info, Msg, __VA_ARGS__ )
#define LOG_WARNING( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Warning, Msg, __VA_ARGS__ )
#define LOG_ERROR( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Error, Msg, __VA_ARGS__ )
#define LOG_FATAL( Instance, Msg, ... ) Instance.Log( ost::log::ELogLevel::Fatal, Msg, __VA_ARGS__ )

#define LOG_TRACE_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Trace, Msg, __VA_ARGS__);
#define LOG_DEBUG_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Debug, Msg, __VA_ARGS__);
#define LOG_INFO_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Info, Msg, __VA_ARGS__);
#define LOG_WARNING_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Warning, Msg, __VA_ARGS__);
#define LOG_ERROR_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Error, Msg, __VA_ARGS__);
#define LOG_FATAL_SCOPE_START( Instance, Msg, ...  ) Instance.LogBeginScope(ost::log::ELogLevel::Fatal, Msg, __VA_ARGS__);

#define LOG_SCOPE_CLOSE( Instance ) Instance.EndLogScope() 

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class LOGGER_API CLogInstance
		{
		public:
			CLogInstance(std::string instanceName);

			void EndLogScope();

			template<typename ... TFmt>
			void LogBeginScope(ELogLevel lvl, std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
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