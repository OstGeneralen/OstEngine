// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/EngineInterface.h"

#include "Application/Config/EngineConfiguration.h"

#include "Rendering/TextureRenderTarget.h"

#include "Subsystem/Input/InputSystem.h"
#include "Subsystem/Input/InputEventProvider.h"
#include "Subsystem/Assets/AssetsSystem.h"

// ------------------------------------------------------------

namespace ost
{
	struct SEngineConfigurations;

	class COstEngine : public IOstEngine
	{
	public:

		void InitSystem_Assets(const std::filesystem::path& assetsRootPath);
		void InitSystem_Rendering(CTextureRenderTarget& engineRenderTarget);
		void InitSystem_Input(input::CInputEventProvider& eventProvider);

		void EngineTick();

	public: // IOstEngine
		IAssetsSystem& GetSystem_Assets() override;
		input::IInputSystem& GetSystem_Input() override;
	
	private:
		input::CInputSystem _inputSystem;
		CAssetsSystem _assetsSystem;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------