// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameBase.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;

    class EditorGameInstance : public GameBase
    {
    public:
        void Load(IAssetManager& assets) override;
        void Unload(IAssetManager& assets) override;
        void Update(Float32 deltaTime) override;

    private:
        UniquePtr<Scene> _editorScene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------