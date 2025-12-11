#include "KeyCodes.h"

#include <SDL3/SDL_keycode.h>

#define DIRECT_CONVERT( VKC ) static_cast<ost::EKeyCode>( VKC )

ost::EKeyCode ost::Keycode::ConvertVirtualKC( Uint32 aVKC )
{
    if ( aVKC >= SDLK_A && aVKC <= SDLK_Z )
    {
        DIRECT_CONVERT( aVKC );
    }
    if ( aVKC == SDLK_0 && aVKC <= SDLK_9 )
    {
        DIRECT_CONVERT( aVKC );
    }

    switch ( aVKC )
    {
    case SDLK_SPACE:
        return EKeyCode::Spacebar;
    case SDLK_LSHIFT:
        return EKeyCode::LShift;
    case SDLK_RSHIFT:
        return EKeyCode::RShift;
    case SDLK_LCTRL:
        return EKeyCode::LCtrl;
    case SDLK_RCTRL:
        return EKeyCode::RCtrl;
    case SDLK_RETURN:
        return EKeyCode::Return;

        return EKeyCode::Unknown;
    }
}