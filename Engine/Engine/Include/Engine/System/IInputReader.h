// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EKeyboard : Uint16
    {
        Unknown,

        LCtrl,
        RCtrl,
        Space,
        Return,
        Esc,
        LShift,
        RShift,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Up,
        Down,
        Left,
        Right,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        NumPad0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,

        COUNT,
    };
    constexpr static SizeType NumKeyboardKeyCodes = static_cast<SizeType>(EKeyboard::COUNT);

    class IInputReader
    {
    public:
        virtual ~IInputReader() = default;

        virtual bool Up(EKeyboard key) const = 0;
        virtual bool Down(EKeyboard key) const = 0;
        virtual bool Pressed(EKeyboard key) const = 0;
        virtual bool Released(EKeyboard key) const = 0;

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------