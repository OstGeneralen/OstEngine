#include "Game.h"
#include <OstEngine/Math/Matrix4x4.h>
#include <OstEngine/Rendering/2D/SpriteRenderer.h>
#include <OstEngine/Rendering/2D/Sprite.h>
#include <OstEngine/Rendering/RenderData/Texture.h>
#include <cmath>

CGame gameInstance;

ost::IGame* GameMain()
{
    return &gameInstance;
}

ost::CTexture texture;
ost::SSprite sprite;
ost::CSpriteRenderer spriteRenderer;

void CGame::Load()
{
    _engine = ost::CEngine::Instance();
    _camera.InitializePerspective( 16.0f / 9.0f, ost::math::Degrees(70.0f) );
    //_camera.InitializeOrthographic( { 16.0f, 9.0f } );  
    _camera.Transform.Translate( { -2.f, 0.0f, -10.0f } );

    spriteRenderer.Initialize();
    texture.LoadDDS( "Assets/Textures/TestTexture.dds" );
    sprite.Texture = &texture;
    //sprite.Transform.Translate( { -1, -1, 0 } );
}

void CGame::Update( const ost::CTimer& aTimer )
{

    _camera.Transform.SetPosition( { sinf( static_cast<Float32>( aTimer.GetTotalTime() ) ) * 5.0f,
                                     cosf( static_cast<Float32>( aTimer.GetTotalTime() ) ) * 5.0f, -10.0f } );
    
    
    ost::Vector3f r = { 0.0f, sinf( static_cast<Float32>( aTimer.GetTotalTime() ) ), 0.0f }; 
    _camera.Transform.SetRotation( r * ost::math::RadToDeg * 0.5f );

    //_camera.Transform.Translate( { 1.0f * aTimer.GetDeltaTime(), 0.0f, 1.0f * aTimer.GetDeltaTime() } );
}

void CGame::Render()
{
    spriteRenderer.Draw( sprite );
    spriteRenderer.Render();
}

const ost::CCamera& CGame::GetCamera() const
{
    return _camera;
}

