// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderQueue.h"

#include <algorithm>

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

void ost::RenderQueue::AddLight(const LightData& light)
{
    _lights.Add(light);
}

void ost::RenderQueue::Push(const DrawCommand& cmd)
{
    _pendingCommands.Add(cmd);
}

void ost::RenderQueue::Finalise()
{
    // Sort by the shader hash
    std::sort( _pendingCommands.begin(), _pendingCommands.end(), []( const DrawCommand& a, const DrawCommand& b ){ return a.ShaderHash() < b.ShaderHash(); } );

    _commands = List<RenderCommand>(_pendingCommands.GetSize());

    // Convert pending commands into actual renderable commands
    for(SizeType i = 0; i < _pendingCommands.GetSize(); ++i)
    {
        _commands[i].pIndexBuffer = &_resourceManager.Get( _pendingCommands[i].indexBuffer );
        _commands[i].pVertexBuffer = &_resourceManager.Get( _pendingCommands[i].vertexBuffer );
        _commands[i].pVertexShader = &_resourceManager.Get( _pendingCommands[i].vertexShader );
        _commands[i].pPixelShader = &_resourceManager.Get( _pendingCommands[i].pixelShader );
        _commands[i].transform = _pendingCommands[i].transform;
    }
}

// ------------------------------------------------------------

void ost::RenderQueue::Clear()
{
    _commands.Clear();
    _lights.Clear();
}

// ------------------------------------------------------------

const RenderView& ost::RenderQueue::GetView() const
{
    return _view;
}

const List<LightData>& ost::RenderQueue::GetLights() const
{
    return _lights;
}

const List<RenderCommand>& ost::RenderQueue::GetRenderCommands() const
{
    return _commands;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------