#pragma once
#include <OstEngine/Rendering/Window.h>
#include <OstEngine/Application/GameInterface.h>
#include <OstEngine/Application/InputReader.h>
#include <OstEngine/Input/InputSystem.h>
#include <OstEngine/Rendering/DX/DXRenderer.h>
#include <OstEngine/Rendering/DX/DXRenderState.h>
#include <OstEngine/Rendering/DX/DXModel.h>
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
        void Run(IGame& aAppInterface);

        CInputSystem& GetInputSystem();
    private:
        void Initialize( HINSTANCE aAppInstance );
        void Deinitialize();

        bool EngineEventProcessor( Uint32 aMsg, Int64 wparam, Uint64 lparam );

        CWindow _window;
        CDXRenderer _dxRenderer;
        CInputReader _inputReader;
        CInputSystem _inputSystem;
        CDXRenderState _defaultRenderState;
        CDXModel _triA;
        CDXModel _triB;

    private:
        CEngine();
        static CEngine* _instancePtr;
        
    };
} // namespace ost