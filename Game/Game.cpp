#include "Game.h"

CGame gameInstance;
ost::IGame* GameMain()
{
    return &gameInstance;
}

void CGame::Load()
{
    _engine = ost::CEngine::Instance();

    ost::STexture* testTexture = _engine->GetTextureLoader().GetTexture( "Assets/Textures/TestTexture.bmp" );
    _testSprite.Create( *testTexture );
}

void CGame::Update()
{
    _frameTimer.Update();
    _testSprite.Location =
        ost::Vector2f{ 100.0f + ( cosf( static_cast<float>( _frameTimer.GetTotalTime() ) ) * 100.0f ),
                       100.0f + ( sinf( static_cast<float>( _frameTimer.GetTotalTime() ) ) * 100.0f ) };
}

void CGame::Render()
{
    _engine->GetRenderer().DrawSprite( _testSprite );
}
