#pragma once
#include "OstEngine/Rendering/Window.h"

#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/IO/Input/InputReader.h>
#include <OstEngine/IO/Input/InputSystem.h>

#include <Windows.h>

namespace ost
{
    class CDXRenderer;

    class CEngine
    {
    public:
        static CEngine* Instance();
        static void InitializeEngine( HINSTANCE aAppInstance );
        static void ShutdownEngine();

    public:
        void Run( IGame& aAppInterface );

        CInputSystem& GetInputSystem();

    private:
        void Initialize( HINSTANCE aAppInstance );
        void Deinitialize();

        bool EngineEventProcessor( Uint32 aMsg, Int64 wparam, Uint64 lparam );

        CWindow _window;
        CInputReader _inputReader;
        CInputSystem _inputSystem;

    private:
        CEngine();
        static CEngine* _instancePtr;
    };
} // namespace ost