// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneViewContext.h"

#include "EditorContext.h"
#include "Editors/SceneView/Commands/SceneViewRendererCommands.h"

#include <GraphicsEngine/IGraphicsEngine.h>
#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Math/Math.h>

using namespace ost;

// ------------------------------------------------------------

SceneViewContext::SceneViewContext(EditorContext& parentContext, IGraphicsEngine& graphicsEngine)
    : _parentContext{parentContext}
    , _currentSceneViewMode{ESceneViewMode::Lit}
    , _gfxEngine{graphicsEngine}
    , _outputRenderer{graphicsEngine.GetRenderer()}
    , _outputSize{_outputRenderer.GetDimensions().VectorCast<Uint32>()}
{
}

// ------------------------------------------------------------

void ost::SceneViewContext::SetSceneViewMode(ESceneViewMode m)
{
    _currentSceneViewMode = m;
}

ESceneViewMode ost::SceneViewContext::GetSceneViewMode() const
{
    return _currentSceneViewMode;
}

// ------------------------------------------------------------

void ost::SceneViewContext::SetOutputSize(const Vector2f& size)
{
    const Vector2u uintSize = size.VectorCast<Uint32>();
    const Float32 aspect = size.X / size.Y;

    if (uintSize == _outputSize || aspect < 0.0001f)
    {
        // Nothing to do, early out :)
        return;
    }

    _outputSize = uintSize;
    _parentContext.commandQueue.PushCommand(Ptr::NewUnique<ResizeSceneViewEditorCommand>());
}

// ------------------------------------------------------------

ImTextureID ost::SceneViewContext::GetSceneViewOutput()
{
    const void* pTexture = nullptr;

    switch (_currentSceneViewMode)
    {
    case ESceneViewMode::Lit:
        pTexture = _outputRenderer.GetOutputTarget(ERenderOutputTexture::Output)->GetNativeResource();
        break;
    case ESceneViewMode::Unlit:
        pTexture = _outputRenderer.GetOutputTarget(ERenderOutputTexture::GBufferAlbedo)->GetNativeResource();
        break;
    case ESceneViewMode::Normals:
        pTexture = _outputRenderer.GetOutputTarget(ERenderOutputTexture::GBufferNormal)->GetNativeResource();
        break;
    case ESceneViewMode::ORM:
        pTexture = _outputRenderer.GetOutputTarget(ERenderOutputTexture::GBufferORM)->GetNativeResource();
        break;
    }

    return (ImTextureID)(intptr_t)pTexture;
}

// ------------------------------------------------------------

void ost::SceneViewContext::ApplyOutputSizeToRenderer()
{
    _gfxEngine.SetRenderSize(_outputSize);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------