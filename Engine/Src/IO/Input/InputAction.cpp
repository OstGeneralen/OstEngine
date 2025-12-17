#include "OstEngine/IO/Input/InputAction.h"

#include "OstEngine/IO/Input/InputSystem.h"

#include <OstEngine/Math/NumericUtils.h>

ost::SInputBinding_Button ost::InputBinding::CreateButton( EKeyCode aKey )
{
    SInputBinding_Button b;
    b.Key = aKey;
    return b;
}
ost::SInputBinding_NegativePositive ost::InputBinding::CreateNegativePositive( EKeyCode aNegative, EKeyCode aPositive )
{
    SInputBinding_NegativePositive b;
    b.Negative = aNegative;
    b.Positive = aPositive;
    return b;
}
ost::SInputBinding_UpDownLeftRight ost::InputBinding::CreateUpDownLeftRight( EKeyCode aUp, EKeyCode aDown,
                                                                             EKeyCode aLeft, EKeyCode aRight )
{
    SInputBinding_UpDownLeftRight b;
    b.Up = aUp;
    b.Down = aDown;
    b.Left = aLeft;
    b.Right = aRight;
    return b;
}

// ------------------------------------------------------------
// BINDING EVALUATIONS
// ------------------------------------------------------------

bool ost::SInputBinding_Button::Evaluate( const CInputReader& aInput, InputValue& outValue )
{
    const bool currentValue = aInput.IsKeyDown( Key );
    outValue.ButtonValue |= currentValue;
    return true;
}

bool ost::SInputBinding_NegativePositive::Evaluate( const CInputReader& aInput, InputValue& outValue )
{
    float newValue = 0.0f;
    if ( aInput.IsKeyDown( Negative ) )
    {
        newValue -= 1.0f;
    }
    if ( aInput.IsKeyDown( Positive ) )
    {
        newValue += 1.0f;
    }
    outValue.Axis1DValue += newValue;
    return true;
}

bool ost::SInputBinding_UpDownLeftRight::Evaluate( const CInputReader& aInput, InputValue& outValue )
{
    float newX = 0.0f;
    float newY = 0.0f;
    if ( aInput.IsKeyDown( Down ) )
    {
        newY += 1.0f;
    }
    if ( aInput.IsKeyDown( Up ) )
    {
        newY -= 1.0f;
    }
    if ( aInput.IsKeyDown( Left ) )
    {
        newX -= 1.0f;
    }
    if ( aInput.IsKeyDown( Right ) )
    {
        newX += 1.0f;
    }
    newX = NumericUtils::Clamp( newX, -1.0f, 1.0f );
    newY = NumericUtils::Clamp( newY, -1.0f, 1.0f );
    const Vector2f newValue{ newX, newY };
    outValue.Axis2DValue += newValue;
    return true;
}

// ------------------------------------------------------------

ost::SInputAction::SInputAction()
    : _actionType{}
    , _callback{}
    , _registerSystemPtr{ nullptr }
    , _bindings{}
    , _value{ { 0.0f, 0.0f } }
{
}

// ------------------------------------------------------------

ost::SInputAction::SInputAction( FInputActionCallback aCallback )
    : _actionType{}
    , _callback{ aCallback }
    , _registerSystemPtr{ nullptr }
    , _bindings{}
    , _value{ { 0.0f, 0.0f } }
{
}

// ------------------------------------------------------------

ost::SInputAction::SInputAction( SInputAction&& aOther ) noexcept
    : SInputAction()
{
    std::swap( _actionType, aOther._actionType );
    std::swap( _callback, aOther._callback );
    std::swap( _registerSystemPtr, aOther._registerSystemPtr );
    std::swap( _bindings, aOther._bindings );
    std::swap( _value, aOther._value );

    if ( _registerSystemPtr )
    {
        _registerSystemPtr->RepointAction( &aOther, this );
    }
}

// ------------------------------------------------------------

ost::SInputAction::~SInputAction()
{
    if ( _registerSystemPtr )
    {
        _registerSystemPtr->UnregisterAction( *this );
    }
    for ( IInputBinding* binding : _bindings )
    {
        delete binding;
    }
}

// ------------------------------------------------------------

ost::SInputAction& ost::SInputAction::operator=( SInputAction&& aOther ) noexcept
{
    std::swap( _actionType, aOther._actionType );
    std::swap( _callback, aOther._callback );
    std::swap( _registerSystemPtr, aOther._registerSystemPtr );
    std::swap( _bindings, aOther._bindings );
    std::swap( _value, aOther._value );

    if ( _registerSystemPtr )
    {
        _registerSystemPtr->RepointAction( &aOther, this );
    }
    return *this;
}

// ------------------------------------------------------------

void ost::SInputAction::Evaluate( const CInputReader& aInput )
{
    InputValue newValue{ { 0.0f, 0.0f } };

    for ( IInputBinding* binding : _bindings )
    {
        binding->Evaluate( aInput, newValue );
    }

    bool shouldInvokeCallback = false;
    switch ( _actionType )
    {
    case ost::EInputActionType::Button:
        shouldInvokeCallback = newValue.ButtonValue != _value.ButtonValue;
        break;
    case ost::EInputActionType::Axis1D:
        newValue.Axis1DValue = NumericUtils::Clamp( newValue.Axis1DValue, -1.0f, 1.0f );
        shouldInvokeCallback = NumericUtils::NearlyEqual( newValue.Axis1DValue, _value.Axis1DValue ) == false;
        break;
    case ost::EInputActionType::Axis2D:
        newValue.Axis2DValue.Normalize();
        shouldInvokeCallback = ( ( newValue.Axis2DValue == _value.Axis2DValue ) == false );
        break;
    }
    _value = newValue;

    if ( shouldInvokeCallback && _callback )
    {
        _callback( _value );
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------