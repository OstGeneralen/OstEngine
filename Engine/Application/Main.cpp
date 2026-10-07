// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Application.h"
#include "Platform/Platform.h"

// ------------------------------------------------------------

int main()
{
    ost::platform::Initialize();
    
    ost::Application app;
    app.Startup();
    app.Run();
    app.Shutdown();

    ost::platform::Shutdown();
    
    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------