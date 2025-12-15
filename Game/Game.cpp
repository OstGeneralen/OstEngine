#include "Game.h"
#include <OstEngine/Math/Matrix4x4.h>

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

    _triangleModel.AddVertex( { -0.5f, -0.5f, 0.0f, 1.0f }, 0x00000000 )
        .AddVertex( { 0.5f, 0.5f, 0.0f, 1.0f }, 0x00000000 )
        .AddVertex( { 0.5f, -0.5f, 0.0f, 1.0f }, 0x00000000 );

    _triangleModel.InitializeResource();

    _colorBuffer.Color = ost::SColorFlt32{ 1.0f, 0.0f, 0.0f, 1.0f };
    _colorConstantBuffer.Initialize( _colorBuffer );

    _renderState = _engine->GetRenderer().CreateRenderState( "Engine/Shaders/DefaultShader" );
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

    _colorBuffer.Color.B = static_cast<float>( ( sin( _frameTimer.GetTotalTime() ) + 1.0 ) / 2.0 );
    _colorBuffer.Color.G = static_cast<float>( ( cos( _frameTimer.GetTotalTime() ) + 1.0 ) / 2.0 );
}

void CGame::Render()
{
    _colorConstantBuffer.Update( _colorBuffer );
    _renderState.Bind();
    _renderState.BindConstantBuffer(_colorConstantBuffer);
    
    _triangleModel.Render();

    _renderState.Unbind();
}

void CGame::InputMove( const ost::InputValue& aValue )
{
    _velocity = aValue.Axis2DValue;
}