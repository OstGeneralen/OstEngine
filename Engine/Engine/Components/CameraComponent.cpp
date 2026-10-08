// Kasper "OstGeneralen" Esbjornsson - 2026
#include "CameraComponent.h"

#include "Engine/Game/Transform.h"
#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

void CameraComponent::MakeOrthographic(Float32 sizeFactorX, Float32 sizeFactorY)
{
    if (_pRenderGraph)
    {
        auto& viewProxy = _pRenderGraph->GetViewProxy();

        viewProxy.projectionType = ViewRenderProxy::EProjectionType::Orthographic;
        viewProxy.lValue = sizeFactorX;
        viewProxy.rValue = sizeFactorY;
    }
}

void CameraComponent::MakePerspective(Float32 vFoV)
{
    if (_pRenderGraph)
    {
        auto& viewProxy = _pRenderGraph->GetViewProxy();
        viewProxy.lValue = vFoV;
        viewProxy.projectionType = ViewRenderProxy::EProjectionType::Perspective;
    }
}

// ------------------------------------------------------------

void ost::CameraComponent::InitializeRenderState(RenderGraph& renderGraph)
{
    _pRenderGraph = &renderGraph;
    GetOwner().transform.OnMarkedDirty.Bind<CameraComponent, &CameraComponent::ProcessTransformChanged>(this);
}

void ost::CameraComponent::DestroyRenderState(RenderGraph& renderGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<CameraComponent, &CameraComponent::ProcessTransformChanged>(this);
    _pRenderGraph = nullptr;
}

void ost::CameraComponent::UpdateDirtyTransform(RenderGraph& renderGraph)
{
    renderGraph.GetViewProxy().transform = GetOwner().transform.GetWorldTransform();
}

void ost::CameraComponent::ProcessTransformChanged()
{
    _pRenderGraph->MarkTransformDirty(*this);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------