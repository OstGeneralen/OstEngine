#include "Engine.h"

ost::CEngine* ost::CEngine::_instancePtr = nullptr;

ost::CEngine* ost::CEngine::Instance() { return _instancePtr; }
