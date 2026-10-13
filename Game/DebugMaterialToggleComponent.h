// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/World/Component.h>

// ------------------------------------------------------------

namespace ost
{
    class StaticMeshComponent;
}

class DebugMaterialToggleComponent : public ost::ActorComponent
{
public:
    DebugMaterialToggleComponent();

    void Start(ost::ComponentContext& context) override;
    void Update(ost::ComponentContext& context) override;

private:
    void SetDisplayDefault();
    void SetDisplayUnlit();
    void SetDisplayNormal();
    void SetDisplayUV();

    ost::StaticMeshComponent* _pTarget;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------