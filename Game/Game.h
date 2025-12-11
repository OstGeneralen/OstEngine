#pragma once
#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Utility/Timer.h>

#include <OstEngine/Rendering/Sprite/SpriteData.h>

class CGame : public ost::IGame
{
public:
    void Load() override;
    void Update() override;
    void Render() override;

private:
    ost::CEngine* _engine;
    ost::SSprite _testSprite;
    ost::CTimer _frameTimer;
};
