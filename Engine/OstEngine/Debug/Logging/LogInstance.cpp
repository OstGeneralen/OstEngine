#include "LogInstance.h"
#include "Logger.h"

// ------------------------------------------------------------

ost::log::CLogInstance::CLogInstance( const std::string& aName )
    : _name{aName}
{
}

// ------------------------------------------------------------

void ost::log::CLogInstance::EndScope()
{
    if (_activeMessageStack.size() == 1)
    {
        // This means we're about to pop the last message so we want to move it across to the logger
        CLogger::Instance()._messages.push_back( _activeMessageStack.top() );
        _activeMessageStack.pop();
    }
    else if ( _activeMessageStack.size() > 1 )
    {
        SLogMessage temp = _activeMessageStack.top();
        _activeMessageStack.pop();
        _activeMessageStack.top().Inner.push_back( temp );
    }
}

// ------------------------------------------------------------

void ost::log::CLogInstance::BeginScope( SLogMessage&& aMsg )
{
    if (_activeMessageStack.empty())
    {
        _activeMessageStack.push( aMsg );
    }
    else
    {
        _activeMessageStack.push( aMsg );
    }
}

// ------------------------------------------------------------

void ost::log::CLogInstance::LogMessage( SLogMessage&& aMsg )
{
    if (_activeMessageStack.empty())
    {
        // If the stack is empty, we just log the message directly
        CLogger::Instance()._messages.push_back( aMsg );
    }
    else
    {
        // Otherwise, add as inner to top of stack
        _activeMessageStack.top().Inner.push_back( aMsg );
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------