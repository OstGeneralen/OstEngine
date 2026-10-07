// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGame;
    extern UniquePtr<IGame> CreateGameInstance();
    class EngineContext;

    class IGame
    {
    public:
        friend class OstEngine;

        virtual ~IGame() = default;

        virtual void Load(EngineContext& context) = 0;
        virtual void Unload(EngineContext& context) = 0;
        virtual void Update(EngineContext& context) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------