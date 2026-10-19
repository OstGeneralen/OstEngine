// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameInterface.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;

    class EditorGameInstance : public IGame
    {
    public:
        void Load(GameContext& context) override;
        void Unload(GameContext& context) override;
        void Update(GameContext& context) override;

    private:
        UniquePtr<IGame> _actualInstance;
        UniquePtr<Scene> _editorScene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------