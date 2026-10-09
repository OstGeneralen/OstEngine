// Kasper "OstGeneralen" Esbjornsson - 2026
#include "CoutLogSink.h"

#include <iostream>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

CoutLogSink::~CoutLogSink()
{
    std::cout.flush();
}

// ------------------------------------------------------------

void CoutLogSink::Receive(const Log::Message& msg)
{
    std::cout << "[" << Log::ILogSink::GetVerbosityStringAbbr(msg.verbosity) << "] " << msg.message << " (" << msg.pCategory->GetName() << ")" << std::endl;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------