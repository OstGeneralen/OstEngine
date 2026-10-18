// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/IOstEngine.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Engine/Platform/Window.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext
    {
    public:
        friend class EditorApplication;

        IOstEngine& coreEngine;
        IGraphicsEngine& graphicsEngine;
        const Window& window;

        static EditorContext& Get();

    private:
        static void Create(IOstEngine& engine, IGraphicsEngine& gfxEngine, const Window& win);
        static void Destroy();

        EditorContext(IOstEngine& engine, IGraphicsEngine& gfxEngine, const Window& win);

        static EditorContext* _pInstance;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------