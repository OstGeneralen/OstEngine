#pragma once
#include <OstEngine/Math/Vectors.h>
#include <OstEngine/Rendering/Window.h>
#include <string>

namespace ost
{
    class COstEngineApp
    {
    protected: // Override these to make your own app
        // clang-format off
        virtual std::string WindowTitle() const { return "OstEngine Window"; }
        virtual Vector2i WindowDimensions() const { return Vector2i( 800, 800 ); }
        // clang-format on

    public:
        void Init();
        void DeInit();
        void Run();

    private:
        CWindow* _appWindow;
    };
} // namespace ost