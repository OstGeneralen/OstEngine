// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/EngineInterface.h"

#include "Application/Config/EngineConfiguration.h"

#include "Rendering/TextureRenderTarget.h"

#include <OstEngine/Game/GameModule.h>
#include <OstEngine/Game/GameInstance.h>
#include <Game/GameModuleInternal.h>

#include "Subsystem/Input/InputSystem.h"
#include "Subsystem/Input/InputEventProvider.h"
#include "Subsystem/Assets/AssetsSystem.h"
#include <OstEngine/ObjectSystem/ObjectSystem.h>

// ------------------------------------------------------------

namespace ost
{
	struct SEngineConfigurations;

	class COstEngine : public IOstEngine
	{
	public:
		void LoadGameModule(const char* moduleName);

		void InitSystem_Assets(const std::filesystem::path& assetsRootPath);
		void InitSystem_Rendering(CTextureRenderTarget& engineRenderTarget);
		void InitSystem_Input(input::CInputEventProvider& eventProvider);

		void EngineTick();

		void Shutdown();

	public: // IOstEngine
		IAssetsSystem& GetSystem_Assets() override;
		input::IInputSystem& GetSystem_Input() override;
	
	private:
		ostengine_internal::CGameModuleLoader _moduleLoader;
		IGameInstance* _gameInstancePtr{ nullptr };

		input::CInputSystem _inputSystem;
		CAssetsSystem _assetsSystem;
		CGameObjectSystem _objectSystem;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------