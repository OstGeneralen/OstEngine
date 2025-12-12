#include "Game.h"
#include <OstEngine/Math/Matrix4x4.h>

CGame gameInstance;
ost::IGame* GameMain()
{
    return &gameInstance;
}

void CGame::Load()
{
    ost::TMatrix4x4<float> ident;
    ost::TMatrix4x4<float> trans;
    trans.M14 = 10;
    trans.M24 = 10;
    trans.M34 = 10;

    ost::TMatrix4x4<float> loc;
    loc.M14 = 2;
    loc.M24 = 4;
    loc.M34 = 6;

    ost::TMatrix4x4<float> mulIdent = trans * ident;
    ost::TMatrix4x4<float> mulLoc = trans * loc;

    const float identX = mulIdent.M14;
    const float identY = mulIdent.M24;
    const float identZ = mulIdent.M34;

    const float mlocX = mulLoc.M14;
    const float mlocY = mulLoc.M24;
    const float mlocZ = mulLoc.M34;

    ost::TVector4<float> testVec{2,4,0,1};

    auto resVec = loc * testVec;

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

    //ost::STexture* testTexture = _engine->GetTextureLoader().GetTexture( "Assets/Textures/TestTexture.bmp" );
    //_testSprite.Create( *testTexture );
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
}

void CGame::Render()
{
    //_engine->GetRenderer().DrawSprite( _testSprite );
}

void CGame::InputMove( const ost::InputValue& aValue )
{
    _velocity = aValue.Axis2DValue;
}