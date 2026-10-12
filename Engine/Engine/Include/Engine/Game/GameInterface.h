// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGame;
    extern UniquePtr<IGame> CreateGameInstance();
    class GameContext;

    class IGame
    {
    public:
        friend class OstEngine;

        virtual ~IGame() = default;

        virtual void Load(GameContext& context) = 0;
        virtual void Unload(GameContext& context) = 0;
        virtual void Update(GameContext& context) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------