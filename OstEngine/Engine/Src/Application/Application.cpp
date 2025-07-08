// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Application/Application.h>

#include <Application/Window/AppWindow.h>
#include <OstEngine/Configuration/CmdArg.h>

#include <EngineCmdArgs.h>
#include <Engine.h>

#include <OstLog/OstLogger.h>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(AppLog);

// ------------------------------------------------------------

ost::CApplication::CApplication(const SAppCmdArgs& cmdArgs)
	: _enginePtr(nullptr)
	, _appWindowPtr(nullptr)
{
	const int32 windowWidth = cmdArgs.ReadWithDefault<int32>(ArgWinWidth, 1600);
	const int32 windowHeight = cmdArgs.ReadWithDefault<int32>(ArgWinHeight, 900);

	_appWindowPtr = new CAppWindow();
	_appWindowPtr->Create(windowWidth, windowHeight, "OstEngine Game");
	_appWindowPtr->InitGUI();
	
	AppLog.Log(OstLogLevel::Info, "Application window created with dimensions {}x{}", windowWidth, windowHeight);

	_enginePtr = new COstEngine(cmdArgs, *_appWindowPtr);
}

// ------------------------------------------------------------

ost::CApplication::~CApplication()
{
}

// ------------------------------------------------------------

void ost::CApplication::Run()
{
	while (_appWindowPtr->ShouldRemainOpen())
	{
		_appWindowPtr->PollEvents();
		_appWindowPtr->BeginWindowRenderFrame();

		_enginePtr->EngineTick();

		_appWindowPtr->EndWindowRenderFrame();
	}

	_enginePtr->Shutdown();

	delete _enginePtr;
	_enginePtr = nullptr;

	_appWindowPtr->Destroy();
	delete _appWindowPtr;
	_appWindowPtr = nullptr;
	
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------