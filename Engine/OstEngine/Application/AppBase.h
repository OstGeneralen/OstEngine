#pragma once
#include <OstEngine/Math/Vectors.h>
#include <OstEngine/Rendering/Window.h>
#include <string>

namespace ost
{
    class CEngine;

    class COstEngineApp
    {
    protected: // Override these to make your own app
        // clang-format off
        virtual std::string WindowTitle() const { return "OstEngine Window"; }
        virtual Vector2i WindowDimensions() const { return Vector2i( 800, 800 ); }
        // clang-format on

        virtual void Init_PreEngine() {}
        virtual void Init_PostEngine( CEngine& aEngine ) {}

        virtual void DeInit_PreEngine( CEngine& aEngine ) {}
        virtual void DeInit_PostEngine() {} 

        virtual void Tick() {}

    public:
        void Init();
        void DeInit();
        void Run();

    private:
        CWindow* _appWindow;
    };
} // namespace ost