// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderQueue.h"

#include "Objects/Model.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

ost::RenderQueue::RenderQueue(const GraphicsResourceManager& resourceManager)
    : _resourceManager{resourceManager}
{
}

// ------------------------------------------------------------

void RenderQueue::SetView(const Matrix4x4& viewProjection, const Matrix4x4& viewInverse)
{
    _view.viewProjection = viewProjection;
    _view.viewInverse = viewInverse;
}

void ost::RenderQueue::Push(ModelCommand&& cmd)
{
    const Model& model = _resourceManager.Get(cmd.hModel);

    for (const HMesh& hSubmesh : model.meshHandles)
    {
        const Mesh* pMesh = &_resourceManager.Get(hSubmesh);

        if(cmd.hMaterialInstances[pMesh->materialIndex].Valid() == false)
        {
            // Fallback on default material?
        }


        RenderCommand renderCmd;
        renderCmd.pMesh = pMesh;
        renderCmd.pModel = &model;
        renderCmd.transform = cmd.transform;
        renderCmd.pMaterialInstance = &_resourceManager.Get(cmd.hMaterialInstances[pMesh->materialIndex]);
        renderCmd.pMaterial = &_resourceManager.Get(renderCmd.pMaterialInstance->GetBaseMaterialHandle());

        _drawCommands.Add(renderCmd);
    }
}

void ost::RenderQueue::Push(LightCommand&& cmd)
{
    _lights.Add(cmd);
}

// ------------------------------------------------------------

void ost::RenderQueue::Clear()
{
    _drawCommands.Clear();
    _lights.Clear();
}

// ------------------------------------------------------------

const RenderView& ost::RenderQueue::GetView() const
{
    return _view;
}

const List<RenderCommand>& ost::RenderQueue::GetDrawCommands() const
{
    return _drawCommands;
}

// ------------------------------------------------------------

const List<LightCommand>& ost::RenderQueue::GetLightCommands() const
{
    return _lights;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------