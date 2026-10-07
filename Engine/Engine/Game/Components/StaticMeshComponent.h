// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Component.h"
#include "GraphicsEngine/Objects/ObjectHandles.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{
    class StaticMeshComponent : public Component
    {
    public:
        StaticMeshComponent(Actor& owner, const ModelHandle& model)
            : Component{owner}
            , _modelHandle{model}
        {
        }
        ModelHandle GetModel() const
        {
            return _modelHandle;
        }

    private:
        ModelHandle _modelHandle;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------