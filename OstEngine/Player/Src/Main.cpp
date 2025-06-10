// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>
#include <OstEngine/Debug/Logging/LogLevel.h>
#include <OstEngine/Debug/Logging/LogMessage.h>
#include <OstEngine/Debug/Logging.h>

int main(int argc, char* argv[])
{
    ost::IOstEngine* engineInstancePtr = ost::CreateEngineInstance({ argv, argc });
    engineInstancePtr->Run();
    ost::ReleaseEngineInstance(&engineInstancePtr);
    return 0;
}



