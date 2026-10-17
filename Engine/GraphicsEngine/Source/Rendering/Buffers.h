// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderPipelineConstants.h"

#include <Math/Color.h>
#include <Math/Matrix4x4.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    struct alignas(16) FrameBufferStructure
    {
        Matrix4x4 viewProjection;
        Matrix4x4 inverseViewProjection;
        Matrix4x4 inverseView;
        Vector4f viewLocation;

        void WriteAndSetBuffer(const Buffer& target, const RenderHardwareInterface& rhi)
        {
            rhi.UpdateBuffer(target, this, sizeof(FrameBufferStructure));
            rhi.SetBuffer(target, PipelineConstant::Get(EBufferSlot::FrameBuffer), EPipelineStage_VS | EPipelineStage_PS);
        }
    };

    struct alignas(16) ObjectBufferStructure
    {
        Matrix4x4 objectTransform;

        void WriteAndSetBuffer(const Buffer& target, const RenderHardwareInterface& rhi)
        {
            rhi.UpdateBuffer(target, this, sizeof(ObjectBufferStructure));
            rhi.SetBuffer(target, PipelineConstant::Get(EBufferSlot::ObjectBuffer), EPipelineStage_VS | EPipelineStage_PS);
        }
    };

    struct alignas(16) LightsBufferStructure
    {
        struct alignas(16) LightDataStruct
        {
            Color color = {0, 0, 0, 0};
            Vector3f position = {0, 0, 0};
            Uint32 type = 0;
            Vector3f direction = {1, 0, 0};
            Float32 radius = 0.5f;
            Float32 outerRadius = 1.0f;
            Float32 range = 1.0f;
            Float32 PADDING[2];
        } lights[8];
        Uint32 numLights = 0;
        Vector3f PADDING0 = {0, 0, 0};

        void WriteAndSetBuffer(const Buffer& target, const RenderHardwareInterface& rhi)
        {
            rhi.UpdateBuffer(target, this, sizeof(LightsBufferStructure));
            rhi.SetBuffer(target, PipelineConstant::Get(EBufferSlot::LightBuffer), EPipelineStage_VS | EPipelineStage_PS);
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------