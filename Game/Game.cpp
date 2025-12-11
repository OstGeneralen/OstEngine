#include "Game.h"

CGame gameInstance;
ost::IGame* GameMain()
{
    return &gameInstance;
}

void CGame::Load()
{
    _moveInputAction = ost::SInputAction( INPUT_CALLBACK( InputMove ) );
    {
        using namespace ost;
        using namespace ost::InputBinding;
        const auto wasdBinding = CreateUpDownLeftRight( EKeyCode::W, EKeyCode::S, EKeyCode::A, EKeyCode::D );
        const auto arwsBinding = CreateUpDownLeftRight( EKeyCode::Up, EKeyCode::Down, EKeyCode::Left, EKeyCode::Right );
        _moveInputAction.AddBinding( wasdBinding );
        _moveInputAction.AddBinding( arwsBinding );
    }

    _engine = ost::CEngine::Instance();
    _engine->GetInputSystem().RegisterAction( _moveInputAction );

    ost::STexture* testTexture = _engine->GetTextureLoader().GetTexture( "Assets/Textures/TestTexture.bmp" );
    _testSprite.Create( *testTexture );
}

void CGame::Update()
{
    _frameTimer.Update();
    float deltaTime = _frameTimer.GetDeltaTime();
    if ( _velocity.MagnitudeSqr() > 0.0f )
    {
        int x = 0;
        x++;
    }
    _testSprite.Location += ( _velocity * 100.0f * _frameTimer.GetDeltaTime() );
}

void CGame::Render()
{
    _engine->GetRenderer().DrawSprite( _testSprite );
}

void CGame::InputMove( const ost::InputValue& aValue )
{
    _velocity = aValue.Axis2DValue;
}