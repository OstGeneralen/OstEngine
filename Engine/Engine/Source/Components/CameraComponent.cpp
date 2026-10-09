// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/CameraComponent.h"

#include "Engine/World/Transform.h"
#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

void CameraComponent::MakeOrthographic(Float32 sizeFactorX, Float32 sizeFactorY)
{
    if (_pSceneGraph)
    {
        auto& viewProxy = _pSceneGraph->GetViewProxy();

        viewProxy.projectionType = ViewRenderProxy::EProjectionType::Orthographic;
        viewProxy.lValue = sizeFactorX;
        viewProxy.rValue = sizeFactorY;
    }
}

void CameraComponent::MakePerspective(Float32 vFoV)
{
    if (_pSceneGraph)
    {
        auto& viewProxy = _pSceneGraph->GetViewProxy();
        viewProxy.lValue = vFoV;
        viewProxy.projectionType = ViewRenderProxy::EProjectionType::Perspective;
    }
}

// ------------------------------------------------------------

void ost::CameraComponent::InitializeRenderState(SceneGraph& SceneGraph)
{
    _pSceneGraph = &SceneGraph;
    GetOwner().transform.OnMarkedDirty.Bind<CameraComponent, &CameraComponent::ProcessTransformChanged>(this);
}

void ost::CameraComponent::DestroyRenderState(SceneGraph& SceneGraph)
{
    GetOwner().transform.OnMarkedDirty.Unbind<CameraComponent, &CameraComponent::ProcessTransformChanged>(this);
    _pSceneGraph = nullptr;
}

void ost::CameraComponent::UpdateDirtyTransform(SceneGraph& SceneGraph)
{
    SceneGraph.GetViewProxy().transform = GetOwner().transform.GetWorldTransform();
}

void ost::CameraComponent::ProcessTransformChanged()
{
    _pSceneGraph->MarkTransformDirty(*this);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------