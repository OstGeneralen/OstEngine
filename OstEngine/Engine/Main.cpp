// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#include <Common/Public/Debugging/Logging/Logging.h>
#include "Engine/Application/CoreEngine.h"


#pragma comment(lib, "Commonx64_Debug")


DEFINE_LOG(MainLogger);


int CommonMain( int argCount, char* args[])
{
	ost::CCoreEngine coreEngine;

	coreEngine.Run();

	return 0;
}



#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ PSTR cmdLine, _In_ INT cmdShow)
{
	AllocConsole();

	FILE* fp = nullptr;
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	return CommonMain(__argc, __argv);
}
#else

int main(int argc, char* args[])
{
	return CommonMain(argc, args);
}
#endif