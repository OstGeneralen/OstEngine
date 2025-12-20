#pragma once
#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>

#include <OstEngine/IO/Input/InputAction.h>

class CGame : public ost::IGame
{
public:
    void Load() override;
    void Update( const ost::CTimer& aTimer ) override;
    void Render() override;

    const ost::CCamera& GetCamera() const override;
    const ost::Vector3f& GetSunDirection() const override;

private:
    ost::CEngine* _engine;
    ost::SInputAction _moveInputAction;
    ost::CCamera _camera;
};
