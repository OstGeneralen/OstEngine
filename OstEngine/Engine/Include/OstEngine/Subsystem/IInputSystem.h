// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

// ------------------------------------------------------------

namespace ost
{
	namespace input
	{
		enum class EKey
		{
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
			NumPad0, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
			LCtrl, RCtrl, LAlt, RAlt, LShift, RShift, 
			Return, Space, Backspace, Esc,
			COUNT,
		};

		class IInputSystem
		{
		public:
			virtual bool KeyDown( EKey k ) const = 0;
			virtual bool KeyUp(EKey k) const = 0;
			virtual bool KeyPressed(EKey k) const = 0;
			virtual bool KeyReleased(EKey k) const = 0;
		};
	}
}

// ------------------------------------------------------------