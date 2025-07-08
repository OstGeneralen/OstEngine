// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/EngineInterface.h"

#include "Rendering/TextureRenderTarget.h"

#include <OstEngine/Game/GameModule.h>
#include <OstEngine/Game/GameInstance.h>
#include <OstEngine/Configuration/AppCmdArgs.h>
#include <Game/GameModuleInternal.h>

#include "Subsystem/Input/InputSystem.h"
#include "Subsystem/Input/InputEventProvider.h"
#include "Subsystem/Assets/AssetsSystem.h"

#include <ObjectSystem/ObjectSystem.h>
// ------------------------------------------------------------

namespace ost
{
	struct SEngineConfigurations;
	class CAppWindow;

	class COstEngine : public IOstEngine
	{
	public:
		COstEngine(const SAppCmdArgs& cmdArgs, CAppWindow& targetWin );

		void LoadGameModule(const char* moduleName);

		void EngineTick();

		void Shutdown();

	public: // IOstEngine
		TPtr<CScene> NewScene(bool makeActive) override;
		void SetActiveScene(TPtr<CScene> scene) override;

	
	private:
		ostengine_internal::CGameModuleLoader _moduleLoader;
		
		CAppWindow* _targetWindowPtr;
		IGameInstance* _gameInstancePtr{ nullptr };

		input::CInputSystem _inputSystem;
		CAssetsSystem _assetsSystem;
		CObjectSystem _objectSystem;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------