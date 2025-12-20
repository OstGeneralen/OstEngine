#include "Game.h"
#include <OstEngine/Common/Math/Matrix4x4.h>
#include <OstEngine/Rendering/2D/SpriteRenderer.h>
#include <OstEngine/Rendering/2D/Sprite.h>
#include <OstEngine/Rendering/RenderData/Texture.h>
#include <OstEngine/Common/Math/AngleUnit.h>
#include <cmath>

CGame gameInstance;

ost::IGame* GameMain()
{
    return &gameInstance;
}

ost::CTexture texture;
ost::SSprite sprite;
ost::SSprite sprite2;
ost::SSprite ground;
ost::CSpriteRenderer spriteRenderer;

ost::Vector3f sunDir;

void CGame::Load()
{
    _engine = ost::CEngine::Instance();
    _camera.InitializePerspective( 16.0f / 9.0f, Degrees(70.0f) );
    //_camera.InitializeOrthographic( { 16.0f, 9.0f } );  
    _camera.Transform.Translate( { 0.f, 2.0f, -10.0f } );
    _camera.Transform.Rotate( {20.0f, 0.0f, 0.0f} );

    spriteRenderer.Initialize();
    texture.LoadDDS( "Assets/Textures/TestTexture.dds" );
    sprite.Texture = &texture;
    sprite2.Texture = &texture;
    ground.Texture = &texture;
    sprite2.Transform.Rotate( { 0, 180.0f, 0 } );
    ground.Transform.Rotate( { 90.0f, 0, 0 } );
    ground.Transform.Translate( { 0, -1.0f, 0 } );
    ground.Transform.Scale( 4.0f );
    //sprite.Transform.Translate( { -1, -1, 0 } );
}

void CGame::Update( const ost::CTimer& aTimer )
{

    //_camera.Transform.SetPosition( { sinf( static_cast<Float32>( aTimer.GetTotalTime() ) ) * 5.0f,
    //                                 cosf( static_cast<Float32>( aTimer.GetTotalTime() ) ) * 5.0f, -10.0f } );
    
    
    //ost::Vector3f r = { 0.0f, sinf( static_cast<Float32>( aTimer.GetTotalTime() ) ), 0.0f }; 
    //_camera.Transform.SetRotation( r * math::RadToDeg * 0.5f );

    //ost::CQuaternion sunRotation({0, cosf((float)aTimer.GetTotalTime()) * math::RadToDeg, 10.0f} );
    _camera.Transform.RotateAround( {0.0f,0.0f,0.0f}, { 0.0f, (45.0f * aTimer.GetDeltaTime()), 0.0f } );
    sunDir = _camera.Transform.InverseTransformDirection( {0,0,1});

    //_camera.Transform.Translate( { 1.0f * aTimer.GetDeltaTime(), 0.0f, 1.0f * aTimer.GetDeltaTime() } );
}

void CGame::Render()
{
    spriteRenderer.Draw( ground );
    spriteRenderer.Draw( sprite );
    spriteRenderer.Draw( sprite2 );
    spriteRenderer.Render();
}

const ost::CCamera& CGame::GetCamera() const
{
    return _camera;
}

const ost::Vector3f& CGame::GetSunDirection() const
{
    return sunDir.GetNormalized();
}

