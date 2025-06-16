// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
// ------------------------------------------------------------
// OstLogger MessageQueue
// ------------------------------------------------------------
// The OstLogger is designed to run on a separate thread for
// message processing to the thread(s) that might produce the
// log messages.
// This queue is designed to enable this behaviour with as 
// little overhead as possible in terms of locks and memory-
// fragmentation.
// It's a circular buffer with a read-head intended to be 
// processed by a single thread (the log thread) and a write-
// head which can be accessed by one or more threads.
// ------------------------------------------------------------

#pragma once
#include "OstLog/LogMessage.h"

#include <atomic>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CMessageQueue
		{
		public:
			CMessageQueue(size_t bufferSize);

			bool Pop(SLogMessage& outMsg);
			void Push(const SLogMessage& msg);
		private:
			const size_t _size;
			SLogMessage* _buffer;

			alignas(64) std::atomic<size_t> _headIdx{ 0 };
			alignas(64) std::atomic<size_t> _tailIdx{ 0 };
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------