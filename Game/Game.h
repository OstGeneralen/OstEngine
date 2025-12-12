#pragma once
#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Utility/Timer.h>
#include <OstEngine/Input/InputAction.h>


class CGame : public ost::IGame
{
public:
    void Load() override;
    void Update() override;
    void Render() override;

private:
    void InputMove( const ost::InputValue& aValue );

    ost::Vector2f _velocity;

    ost::CEngine* _engine;
    ost::CTimer _frameTimer;
    
    ost::SInputAction _moveInputAction;
};
