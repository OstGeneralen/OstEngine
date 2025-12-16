#include "InputSystem.h"
#include "../Input/InputAction.h"
#include <algorithm>

ost::CInputSystem::~CInputSystem()
{
    for (SInputAction* actionPtr : _actions)
    {
        // "Unregister"
        actionPtr->_registerSystemPtr = nullptr;
    }
}

void ost::CInputSystem::Update( const CInputReader& aInput )
{
    for (SInputAction* actionPtr : _actions)
    {
        actionPtr->Evaluate( aInput );
    }
}

void ost::CInputSystem::RegisterAction( SInputAction& aAction )
{
    _actions.push_back( &aAction );
    aAction._registerSystemPtr = this;
}

void ost::CInputSystem::UnregisterAction( SInputAction& aAction )
{
    auto found = std::find( _actions.begin(), _actions.end(), &aAction );
    if (found != _actions.end())
    {
        _actions.erase( found );
    }
    aAction._registerSystemPtr = nullptr;
}

void ost::CInputSystem::RepointAction( SInputAction* aOldPtr, SInputAction* aNewPtr )
{
    for (Uint32 i = 0; i < _actions.size(); ++i)
    {
        if (_actions[i] == aOldPtr)
        {
            _actions[i] = aNewPtr;
            break;
        }
    }
}
