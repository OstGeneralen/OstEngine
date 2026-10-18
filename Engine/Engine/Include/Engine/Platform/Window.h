// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/System/InputReader.h"

#include <OstTypes.h>
#include <functional>

#include <Container/List.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct NativeWindowEventContext
    {
        void* nativeWindowHandle;
        Uint32 message;
        Uint64 wParam;
        Int64 lParam;
    };

    // ------------------------------------------------------------

    using NativeWindowEventCallback = std::function<bool(const NativeWindowEventContext&)>;

    // ------------------------------------------------------------

    class IWindowHost
    {
    public:
        virtual ~IWindowHost() = default;

        virtual void RequestExit() = 0;
        virtual void Resized() = 0;
        virtual void ProcessKeyEvent(EKeyboard key, bool state) = 0;
    };

    // ------------------------------------------------------------

    class Window
    {
    public:
        Window() = default;
        ~Window() = default;

        void Create(IWindowHost& host, const std::string& title, const Vector2u& size, bool fullscreen);
        void Close();

        void Update();

        void AddNativeWindowEventCallback( NativeWindowEventCallback callback );

        Vector2u GetWindowSize() const;
        Vector2u GetClientSize() const;

        void* GetNativeWindowHandle() const;

        bool InstanceWindowProcedure( const NativeWindowEventContext& ctx );

    private:
        IWindowHost* _pHost = nullptr;
        List<NativeWindowEventCallback> _nativeEventCallbacks;
        void* _nativeWindowHandle = nullptr;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------