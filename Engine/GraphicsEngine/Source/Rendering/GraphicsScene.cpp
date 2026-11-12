// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsScene.h"

#include "Resources/GraphicsResourceManager.h"

#include <algorithm>

#include <Utility/Hash.h>

// ------------------------------------------------------------

namespace sorting
{
    static bool GraphicsSceneObjectSort(const ost::GraphicsSceneObject& a, const ost::GraphicsSceneObject& b)
    {
        Uint64 aShaderArr[2] = {a.vertexShader.AsInteger(), a.pixelShader.AsInteger()};
        Uint64 bShaderArr[2] = {b.vertexShader.AsInteger(), b.pixelShader.AsInteger()};
        Uint64 aBufferArr[2] = {a.vertexBuffer.AsInteger(), a.indexBuffer.AsInteger()};
        Uint64 bBufferArr[2] = {b.vertexBuffer.AsInteger(), b.indexBuffer.AsInteger()};

        const Uint64 shaderMask = 0xFFFFFFFF00000000u;
        const Uint64 bufferMask = 0x00000000FFFFFFFFu;

        const Uint64 aHash = (ost::hash::fnv1a<2>(aShaderArr) & shaderMask) | (ost::hash::fnv1a<2>(aBufferArr) & bufferMask);
        const Uint64 bHash = (ost::hash::fnv1a<2>(bShaderArr) & shaderMask) | (ost::hash::fnv1a<2>(bBufferArr) & bufferMask);
        return aHash < bHash;
    }

    static bool RenderLightSort(const ost::LightData& a, const ost::LightData& b)
    {
        return a.type < b.type;
    }
} // namespace sorting

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

void ost::GraphicsScene::SetCamera(const GraphicsSceneCamera& camera)
{
    _pendingCamera = camera;
}

void ost::GraphicsScene::AddObject(const GraphicsSceneObject& object)
{
    _pendingObjects.Add(object);
}

void ost::GraphicsScene::AddLight(const GraphicsSceneLight& light)
{
    _pendingLights.Add(light.data);
}

// ------------------------------------------------------------

void ost::GraphicsScene::Clear()
{
    _pendingCamera = {};
    _pendingLights.Clear();
    _pendingObjects.Clear();
}

void ost::GraphicsScene::PrepareData(const GraphicsResourceManager& resources, const Vector2f& outputDimensions)
{
    // Sort objects by shader + buffer
    std::sort(_pendingObjects.begin(), _pendingObjects.end(), &sorting::GraphicsSceneObjectSort);

    // Sort lights to be directional first
    std::sort(_pendingLights.begin(), _pendingLights.end(), &sorting::RenderLightSort);

    // Build the buffers
    // 1. Frame Buffer
    _frameBufferData = {};
    Matrix4x4 projection;

    const Float32 np = _pendingCamera.nearDistance;
    const Float32 fp = _pendingCamera.farDistance;
    const Float32 sx = _pendingCamera.sizeFactors.X * outputDimensions.X;
    const Float32 sy = _pendingCamera.sizeFactors.Y * outputDimensions.Y;

    switch (_pendingCamera.projectionType)
    {
    case EGraphicsSceneCameraProjection::Ortho: {
        projection = Matrix4x4::CreateOrthographicsProjection(sx, sy, np, fp);
        break;
    }
    case EGraphicsSceneCameraProjection::Persp: {
        projection = Matrix4x4::CreatePerspectiveProjection(_pendingCamera.yFoV, sx / sy, np, fp);
        break;
    }
    }

    const Matrix4x4 view = _pendingCamera.transform.GetInverse();
    _frameBufferData.inverseView = _pendingCamera.transform;
    _frameBufferData.viewProjection = view * projection;
    _frameBufferData.inverseViewProjection = _frameBufferData.viewProjection.GetInverse();
    _frameBufferData.viewLocation = _pendingCamera.transform.ExtractTranslation();

    // 2. Light Buffers
    _lightBuffersData.Clear();
    _lightBuffersData.Reserve(_pendingLights.GetSize() / 8);

    LightsBufferStructure* pCurrentLightBuffer;
    pCurrentLightBuffer = &_lightBuffersData.Emplace();
    pCurrentLightBuffer->numLights = 0;

    for (SizeType i = 0; i < _pendingLights.GetSize(); ++i)
    {
        if (pCurrentLightBuffer->numLights == 8)
        {
            pCurrentLightBuffer = &_lightBuffersData.Emplace();
            pCurrentLightBuffer->numLights = 0;
        }

        pCurrentLightBuffer->lights[pCurrentLightBuffer->numLights].FromLightData(_pendingLights[i]);
        pCurrentLightBuffer->numLights++;
    }

    // 3. Render Commands
    _commands = List<RenderCommand>(_pendingObjects.GetSize());

    for (SizeType i = 0; i < _pendingObjects.GetSize(); ++i)
    {
        _commands[i].pIndexBuffer = &resources.Get(_pendingObjects[i].indexBuffer);
        _commands[i].pVertexBuffer = &resources.Get(_pendingObjects[i].vertexBuffer);
        _commands[i].pVertexShader = &resources.Get(_pendingObjects[i].vertexShader);
        _commands[i].pPixelShader = &resources.Get(_pendingObjects[i].pixelShader);
        _commands[i].transform = _pendingObjects[i].transform;
    }

    // Now clear the pending lists!
    _pendingLights.Clear();
    _pendingObjects.Clear();
    _pendingCamera = {};
}

// ------------------------------------------------------------

const FrameBufferStructure& ost::GraphicsScene::GetFrameBufferData() const
{
    return _frameBufferData;
}

const List<LightsBufferStructure>& ost::GraphicsScene::GetLightBuffersData() const
{
    return _lightBuffersData;
}

const List<RenderCommand>& ost::GraphicsScene::GetRenderCommands() const
{
    return _commands;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------