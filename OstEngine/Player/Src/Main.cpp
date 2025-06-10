// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>

int main(int argc, char* argv[])
{
    ost::IOstEngine* engineInstancePtr = ost::CreateEngineInstance({ argv, argc });
    engineInstancePtr->Run();
    ost::ReleaseEngineInstance(&engineInstancePtr);
    return 0;
}



