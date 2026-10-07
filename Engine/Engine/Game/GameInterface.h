// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGame;
    extern UniquePtr<IGame> CreateGameInstance();

    class IGame
    {
    public:
        friend class OstEngine;

        virtual ~IGame() = default;

        virtual void Load() = 0;
        virtual void Unload() = 0;

        virtual void Update(Float32 deltaTime) = 0;

        OstEngine& GetEngine()
        {
            return *_pEngine;
        }
        const OstEngine& GetEngine() const
        {
            return *_pEngine;
        }

    private:
        OstEngine* _pEngine;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------