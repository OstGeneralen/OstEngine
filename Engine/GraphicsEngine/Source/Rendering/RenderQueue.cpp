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

void RenderQueue::SetView(const Matrix4x4& view)
{
    _view = view;
}

void ost::RenderQueue::Push(ModelCommand&& cmd)
{
    const Model& model = _resourceManager.Get(cmd.hModel);

    for (const HMesh& hSubmesh : model.meshHandles)
    {
        RenderCommand renderCmd;
        renderCmd.pMesh = &_resourceManager.Get(hSubmesh);
        renderCmd.transform = cmd.transform;
        renderCmd.pMaterialInstance = &_resourceManager.Get(cmd.hMaterialInstance);
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

const Matrix4x4& ost::RenderQueue::GetView() const
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