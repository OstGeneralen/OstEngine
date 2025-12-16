#pragma once
#include <OstEngine/IO/Input/InputReader.h>
#include <OstEngine/IO/Input/KeyCodes.h>
#include <OstEngine/IO/Input/InputActionType.h>
#include <OstEngine/IO/Input/InputValue.h>

#include <cassert>
#include <functional>
#include <vector>

#define INPUT_CALLBACK( functionName ) [&]( auto iv ) { functionName##(iv); }

namespace ost
{
    using FInputActionCallback = std::function<void( const InputValue& )>;

    struct IInputBinding
    {
        virtual ~IInputBinding() = default;
        virtual bool Evaluate( const CInputReader& aInput, InputValue& outValue ) = 0;
    };

    struct SInputBinding_Button : IInputBinding
    {
        EKeyCode Key = EKeyCode::Unknown;
        EInputActionType GetType() const
        {
            return EInputActionType::Button;
        }
        bool Evaluate( const CInputReader& aInput, InputValue& outValue ) final override;
    };

    struct SInputBinding_NegativePositive : IInputBinding
    {
        EKeyCode Positive = EKeyCode::Unknown;
        EKeyCode Negative = EKeyCode::Unknown;

        EInputActionType GetType() const
        {
            return EInputActionType::Axis1D;
        }
        bool Evaluate( const CInputReader& aInput, InputValue& outValue ) final override;
    };

    struct SInputBinding_UpDownLeftRight : IInputBinding
    {
        EKeyCode Up = EKeyCode::Unknown;
        EKeyCode Down = EKeyCode::Unknown;
        EKeyCode Left = EKeyCode::Unknown;
        EKeyCode Right = EKeyCode::Unknown;
        
        EInputActionType GetType() const
        {
            return EInputActionType::Axis2D;
        }
        bool Evaluate( const CInputReader& aInput, InputValue& outValue ) final override;
    };

    namespace InputBinding
    {
        static SInputBinding_Button CreateButton( EKeyCode aKey )
        {
            SInputBinding_Button b;
            b.Key = aKey;
            return b;
        }
        static SInputBinding_NegativePositive CreateNegativePositive( EKeyCode aNegative, EKeyCode aPositive )
        {
            SInputBinding_NegativePositive b;
            b.Negative = aNegative;
            b.Positive = aPositive;
            return b;
        }
        static SInputBinding_UpDownLeftRight CreateUpDownLeftRight( EKeyCode aUp, EKeyCode aDown, EKeyCode aLeft,
                                                                    EKeyCode aRight )
        {
            SInputBinding_UpDownLeftRight b;
            b.Up = aUp;
            b.Down = aDown;
            b.Left = aLeft;
            b.Right = aRight;
            return b;
        }
    } // namespace InputBinding

    struct SInputAction
    {
        friend class CInputSystem;

    public:
        SInputAction();
        SInputAction( FInputActionCallback aCallback );
        SInputAction( SInputAction&& aOther ) noexcept;
        ~SInputAction();

        SInputAction& operator=( SInputAction&& aOther ) noexcept;

        SInputAction( const SInputAction& ) = delete;

        template <typename TBindingType>
        void AddBinding( const TBindingType& aBinding )
        {
            if ( _bindings.size() == 0 )
            {
                _actionType = aBinding.GetType();
            }
            else
            {
                assert( _actionType == aBinding.GetType() && "Action types may not mismatch" );
            }
            _bindings.push_back( new TBindingType( aBinding ) );
        }

        void Evaluate( const CInputReader& aInput );

    private:
        EInputActionType _actionType;
        FInputActionCallback _callback;
        CInputSystem* _registerSystemPtr;
        std::vector<IInputBinding*> _bindings;
        InputValue _value;
    };

} // namespace ost