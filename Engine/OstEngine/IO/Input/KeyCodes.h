#pragma once
#include <OstEngine/Types.h>

namespace ost
{
    enum class EKeyCode : Uint8
    {
        Unknown = 0,
        Spacebar,
        LShift, RShift,
        LCtrl, RCtrl,
        Return,

        Left, Right, Up, Down,

        // Num (top bar) keys
        // 48 to 57
        Num0 = '0', 
        Num1,       
        Num2,       
        Num3,       
        Num4,       
        Num5,       
        Num6,       
        Num7,       
        Num8,       
        Num9,       

        // Letter Keys
        // 97 to 122
        A = 'a',    
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

        Count = 0xFFu, 
	};

    namespace Keycode
    {
        constexpr static Uint8 KeyCount = static_cast<Uint8>( EKeyCode::Count );

        extern EKeyCode ConvertVirtualKC( Uint32 aVKC );
    }
}