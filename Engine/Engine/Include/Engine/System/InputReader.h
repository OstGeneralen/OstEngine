// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/System/IInputReader.h"

#include <OstTypes.h>
#include <bitset>

// ------------------------------------------------------------

namespace ost
{

    class InputReader : public IInputReader
    {
    public:
        void EndFrame();
        void ProcessKeyEvent(EKeyboard key, bool pressed);

        bool Up(EKeyboard key) const override;
        bool Down(EKeyboard key) const override;
        bool Pressed(EKeyboard key) const override;
        bool Released(EKeyboard key) const override;

    private:
        struct
        {
            std::bitset<NumKeyboardKeyCodes> current;
            std::bitset<NumKeyboardKeyCodes> previous;
        } _keyboardState;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------