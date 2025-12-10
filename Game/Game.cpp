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

}

void CGame::Render()
{
    _engine->GetRenderer().DrawSprite( _testSprite );
}
