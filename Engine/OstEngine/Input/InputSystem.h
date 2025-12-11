#pragma once
#include <OstEngine/Application/InputReader.h>
#include <vector>

namespace ost
{
    struct SInputAction;

    class CInputSystem
    {
    public:
        ~CInputSystem();
        void Update( const CInputReader& aInput);

        void RegisterAction( SInputAction& aAction );
        void UnregisterAction( SInputAction& aAction );
        void RepointAction( SInputAction* aOldPtr, SInputAction* aNewPtr );

    private:
        std::vector<SInputAction*> _actions;
    };
} // namespace ost