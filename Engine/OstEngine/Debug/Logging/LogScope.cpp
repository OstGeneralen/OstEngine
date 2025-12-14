#include <OstEngine/OstEngineMinimal.h>
#include "LogScope.h"

#include "Logger.h"

void ost::log::SLogScope::PushLevel()
{
    _currentDepth++;
}

void ost::log::SLogScope::PopLevel()
{
    OST_ASSERT( _currentDepth > 0, "Pop is not valid on depth 0" );
    _currentDepth--;
}

void ost::log::SLogScope::Log()
{
    std::string contentStr;
    GenerateString( contentStr );
    Logging::Log( "{}", contentStr );
}

void ost::log::SLogScope::Confirm()
{
    std::string contentStr;
    GenerateString( contentStr );
    Logging::Confirm( "{}", contentStr );
}

void ost::log::SLogScope::Warning()
{
    std::string contentStr;
    GenerateString( contentStr );
    Logging::Warning( "{}", contentStr );
}

void ost::log::SLogScope::Error()
{
    std::string contentStr;
    GenerateString( contentStr );
    Logging::Error( "{}", contentStr );
}

void ost::log::SLogScope::GenerateString( std::string& aOutStr )
{
    std::stringstream str;
    str << _topMessage << '\n';
    for ( Int32 i = 0; i < _subMessages.size(); ++i )
    {
        str << '\t';
        for ( Int32 depth = 0; depth < _subMessages[i].depth; ++depth )
        {
            str << '\t';
        }
        str << _subMessages[i].content;
        if ( i + 1 < _subMessages.size() )
        {
            str << '\n';
        }
    }

    aOutStr = str.str();
}