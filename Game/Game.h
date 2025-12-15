#pragma once
#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Engine.h>
#include <OstEngine/Utility/Timer.h>
#include <OstEngine/Input/InputAction.h>

#include <OstEngine/Rendering/DX/DXRenderState.h>
#include <OstEngine/Rendering/DX/DXConstantBuffer.h>
#include <OstEngine/Rendering/RenderCore.h>
#include <OstEngine/Math/Color.h>


CBUFFER_STRUCTURE struct ColorBuffer
{
    ost::SColorFlt32 Color;
};

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

    ColorBuffer _colorBuffer;
    ost::CDXRenderState _renderState;
    ost::CDXModel _triangleModel;
    ost::CDXConstantBuffer _colorConstantBuffer;
};
