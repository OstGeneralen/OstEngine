// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Engine.h"
#include "Application/Config/ConfigFile.h"

#include <OstLog/OstLogger.h>


OSTLOG_LOG_INSTANCE(OstEngineLog);

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Assets(const std::filesystem::path& assetsRootPath)
{
	_assetsSystem.SetRootPath(assetsRootPath);
}

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Rendering(CTextureRenderTarget& engineRenderTarget)
{
}

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Input(input::CInputEventProvider& eventProvider)
{
	eventProvider.BindInputSystem(_inputSystem);
}

// ------------------------------------------------------------

ost::IAssetsSystem& ost::COstEngine::GetSystem_Assets()
{
	return _assetsSystem;
}

// ------------------------------------------------------------

ost::input::IInputSystem& ost::COstEngine::GetSystem_Input()
{
	return _inputSystem;
}

// ------------------------------------------------------------

void ost::COstEngine::EngineTick()
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------