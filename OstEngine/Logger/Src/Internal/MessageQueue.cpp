// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Internal/MessageQueue.h"
#include <exception>

// ------------------------------------------------------------

ost::log::CMessageQueue::CMessageQueue(size_t bufferSize)
	: _size(bufferSize)
	, _buffer{new SLogMessage[_size]}
{
}

// ------------------------------------------------------------

bool ost::log::CMessageQueue::Pop(SLogMessage& outMsg)
{
	if (_headIdx == _tailIdx)
	{
		// Nothing to pop
		return false;
	}

	const size_t head = _headIdx;
	outMsg = _buffer[head];
	const size_t newHead = (head + 1) % _size;
	_headIdx = newHead;
	return true;
}

// ------------------------------------------------------------

void ost::log::CMessageQueue::Push(const SLogMessage& msg)
{

	const size_t tail = _tailIdx;
	const size_t newTail = (tail + 1) % _size;
	if (newTail == _headIdx)
	{
		// This is a problem, we've not processed the queue fast enough to actually deal with all the messages here
		throw std::exception("MessageQueue: Tail outpaced head. Increase buffer size or quicken message processing");
	}
	_buffer[tail] = msg;
	_tailIdx = newTail;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------