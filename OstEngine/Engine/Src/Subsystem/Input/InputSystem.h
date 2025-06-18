// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Subsystem/IInputSystem.h"
#include <bitset>

// ------------------------------------------------------------

namespace ost
{
	namespace input
	{
		class CInputSystem : public IInputSystem
		{
		public:
			void NewInputFrame();
			void NotifyKeyChange(EKey k, bool state);


		public: // IInputHandler
			bool KeyDown(EKey k) const;
			bool KeyUp(EKey k) const;
			bool KeyPressed(EKey k) const;
			bool KeyReleased(EKey k) const;

		private:
			using KeyState = std::bitset<static_cast<uint64>(EKey::COUNT)>;
			
			KeyState& KeyStateCurrent();
			KeyState& KeyStatePrevious();
			const KeyState& KeyStateCurrent() const;
			const KeyState& KeyStatePrevious() const;

			KeyState _keyStateBuffer[2];
			uint32 _currentState = 0;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------