// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/OstGui.h"

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;
    class IGraphicsEngine;
    class IRenderer;

    enum class ESceneViewMode
    {
        Lit,
        Unlit,
        Normals,
        Depth,
        ORM,
    };

    class SceneViewContext
    {
    public:
        SceneViewContext(EditorContext& parentContext, IGraphicsEngine& graphicsEngine);

        void SetSceneViewMode(ESceneViewMode m);
        ESceneViewMode GetSceneViewMode() const;

        void SetOutputSize(const Vector2f& size);
        ImTextureID GetSceneViewOutput();

        // Don't call this during editor gui drawing!
        // Use "SetOutputSize" instead as this will fire the command which will safely invoke this
        void ApplyOutputSizeToRenderer();

    private:
        EditorContext& _parentContext;

        ESceneViewMode _currentSceneViewMode;
        
        IGraphicsEngine& _gfxEngine;
        IRenderer& _outputRenderer;

        Vector2u _outputSize;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------