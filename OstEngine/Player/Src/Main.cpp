// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Application/Application.h>


// ------------------------------------------------------------

int main(int argc, char* argv[])
{
    ost::SCommandArgs cmdArgs(argv, argc);
    ost::CApplication app{ cmdArgs };
    app.Run();
    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------