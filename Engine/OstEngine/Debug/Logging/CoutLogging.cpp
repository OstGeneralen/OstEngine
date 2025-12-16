#include "CoutLogging.h"

#include <Windows.h>
#include <iostream>

#define CCOLOR_GRAY 8
#define CCOLOR_RED 12
#define CCOLOR_GREEN 10
#define CCOLOR_YELLOW 14
#define CCOLOR_WHITE 7

// ------------------------------------------------------------

namespace
{
    int LogLevelToColor( ost::log::ELogLevel l )
    {
        switch ( l )
        {
        case ost::log::ELogLevel::Message:
            return CCOLOR_WHITE;
        case ost::log::ELogLevel::Confirm:
            return CCOLOR_GREEN;
        case ost::log::ELogLevel::Warning:
            return CCOLOR_YELLOW;
        case ost::log::ELogLevel::Error:
            return CCOLOR_RED;
        }

        return CCOLOR_WHITE;
    }

    void SetColor( int aColorCode )
    {
        HANDLE cHnd = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( cHnd, aColorCode );
    }

    void PrintMessage(const ost::log::SLogMessage& aMsg, int aLevel)
    {
        if (aLevel == 0)
        {
            ::SetColor( CCOLOR_GRAY );
            std::cout << '[' << aMsg.FormattedTime << "] ";
            ::SetColor( ::LogLevelToColor( aMsg.Verbosity ) );
            std::cout << aMsg.Message << '\n';
        }
        else
        {
            ::SetColor( CCOLOR_GRAY );
            std::cout << " ........ ";
            for (int i = 0; i < aLevel; ++i)
            {
                std::cout << "  ";
            }
            ::SetColor( ::LogLevelToColor( aMsg.Verbosity ) );
            std::cout << aMsg.Message << '\n';
        }

        for (const auto& subMsg : aMsg.Inner)
        {
            PrintMessage( subMsg, aLevel + 1 );
        }
    }
} // namespace

// ------------------------------------------------------------

void ost::log::StdOutLog( const SLogMessage& aMsg )
{
    ::PrintMessage( aMsg, 0 );
    std::cout.flush();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------