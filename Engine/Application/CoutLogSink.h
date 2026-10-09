// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstLogSink.h>

// ------------------------------------------------------------

namespace ost
{
    class CoutLogSink : public Log::ILogSink
    {
    public: // Log::ILogSink
        ~CoutLogSink();
        void Receive( const Log::Message& msg ) override;
    };  
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------