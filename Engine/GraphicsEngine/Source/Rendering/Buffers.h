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
        struct alignas(16)
        {
            Vector4f direction = {0.0f, -1.0f, 0.0f, 0.0f};
            Color color = Colors::Black;
        } directional;

        struct alignas(16)
        {
            Color color = Colors::Black;
        } ambient;

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