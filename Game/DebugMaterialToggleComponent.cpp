// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DebugMaterialToggleComponent.h"

#include <Engine/Components/StaticMeshComponent.h>
#include <Engine/System/InputReader.h>
#include <Engine/World/Actor.h>
#include <Engine/World/ComponentContext.h>

// ------------------------------------------------------------

DebugMaterialToggleComponent::DebugMaterialToggleComponent()
{
    AddFlag(ost::EComponentFlag::Ticked);
}

void DebugMaterialToggleComponent::Start(ost::ComponentContext& context)
{
    _pTarget = GetOwner().GetComponent<ost::StaticMeshComponent>();
    SetDisplayDefault();
}

void DebugMaterialToggleComponent::Update(ost::ComponentContext& context)
{
    if(context.Input().Pressed(ost::EKeyboard::Num1))
    {
        SetDisplayDefault();
    }
    if(context.Input().Pressed(ost::EKeyboard::Num2))
    {
        SetDisplayUnlit();
    }
    if(context.Input().Pressed(ost::EKeyboard::Num3))
    {
        SetDisplayNormal();
    }
    if(context.Input().Pressed(ost::EKeyboard::Num4))
    {
        SetDisplayUV();
    }
}

void DebugMaterialToggleComponent::SetDisplayDefault()
{
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_default", 1u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_unlit", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_normals", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_uv", 0u);
}

void DebugMaterialToggleComponent::SetDisplayUnlit()
{
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_default", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_unlit", 1u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_normals", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_uv", 0u);
}

void DebugMaterialToggleComponent::SetDisplayNormal()
{
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_default", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_unlit", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_normals", 1u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_uv", 0u);
}

void DebugMaterialToggleComponent::SetDisplayUV()
{
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_default", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_unlit", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_normals", 0u);
    _pTarget->GetMaterial()->Properties().SetProperty("OUTPUT_uv", 1u);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------