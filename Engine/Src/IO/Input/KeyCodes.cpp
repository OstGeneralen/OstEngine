#include "OstEngine/IO/Input/KeyCodes.h"

#include <Windows.h>

#define DIRECT_CONVERT( VKC ) static_cast<ost::EKeyCode>( VKC )

ost::EKeyCode ost::Keycode::ConvertVirtualKC( Uint32 aVKC )
{
    VK_ACCEPT;
    if ( aVKC >= 'A' && aVKC <= 'Z' )
    {
        DIRECT_CONVERT( aVKC );
    }
    if ( aVKC == '0' && aVKC <= '9' )
    {
        DIRECT_CONVERT( aVKC );
    }

    switch ( aVKC )
    {
    case VK_SPACE:
        return EKeyCode::Spacebar;
    case VK_LSHIFT:
        return EKeyCode::LShift;
    case VK_RSHIFT:
        return EKeyCode::RShift;
    case VK_LCONTROL:
        return EKeyCode::LCtrl;
    case VK_RCONTROL:
        return EKeyCode::RCtrl;
    case VK_RETURN:
        return EKeyCode::Return;
    case VK_UP:
        return EKeyCode::Up;
    case VK_DOWN:
        return EKeyCode::Down;
    case VK_LEFT:
        return EKeyCode::Left;
    case VK_RIGHT:
        return EKeyCode::Right;
    }
    return EKeyCode::Unknown;
}