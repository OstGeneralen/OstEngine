// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/IOstEngine.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Engine/Platform/Window.h>
#include "Services/ServiceLocator.h"

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext
    {
    public:
        friend class EditorApplication;

        const Window& window;
        ServiceLocator& serviceLocator;

        static EditorContext& Get();

    private:
        static void Create(ServiceLocator& sl, const Window& win);
        static void Destroy();

        EditorContext(ServiceLocator& sl, const Window& win);

        static EditorContext* _pInstance;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------