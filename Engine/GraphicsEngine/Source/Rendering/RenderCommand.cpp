// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderCommand.h"

// Resources and Objects
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialUtility.h"
#include "Objects/Buffer.h"

// Contextual
#include "RenderCommandContext.h"
#include "Resources/GraphicsResourceManager.h"

// RHI
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/Buffers.h"
#include "Rendering/RenderPipelineConstants.h"

using namespace ost;

// ------------------------------------------------------------

void RenderCommand::Execute(RenderCommandContext& ctx, const Buffer& objectBuffer) const
{
    const EPipelineStage_ PipelineALL = EPipelineStage_PS | EPipelineStage_VS;

    if (ctx.pCurrentMaterial != pMaterial)
    {
        ctx.pCurrentMaterial = pMaterial;
        ctx.RHI.SetPSO(pMaterial->GetPSO());
    }
    if (ctx.pCurrentMaterianInstance != pMaterialInstance)
    {
        ctx.pCurrentMaterianInstance = pMaterialInstance;

        // Update Material Instance Property Buffer
        const auto& propertyBuffer = pMaterialInstance->GetPropertiesBuffer();
        ctx.RHI.UpdateBuffer(propertyBuffer, pMaterialInstance->GetPropertiesData(), pMaterialInstance->GetPropertiesDataSize());
        ctx.RHI.SetBuffer(propertyBuffer, PipelineConstant::Get(EBufferSlot::MaterialProperties), PipelineALL);

        // Set Material Instance Textures
        for (SizeType i = 0; i < MaterialTextureCount; ++i)
        {
            const EMaterialTexture materialTexture = static_cast<EMaterialTexture>(i);
            const Uint32 bindSlot = PipelineConstant::Get(MaterialTextureToBindSlot(materialTexture));

            if (pMaterialInstance->Textures().HasTexture(materialTexture))
            {
                const Texture& texture = ctx.Resources.Get(pMaterialInstance->Textures().GetTexture(materialTexture));
                ctx.RHI.SetTexture(texture, bindSlot, EPipelineStage_PS);
            }
        }
    }

    ObjectBufferStructure objectBufferData = {};
    objectBufferData.objectTransform = transform;
    ctx.RHI.UpdateBuffer(objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure));
    ctx.RHI.SetBuffer(objectBuffer, PipelineConstant::Get(EBufferSlot::ObjectBuffer), PipelineALL);

    ctx.RHI.Draw(*pMesh, pMesh != ctx.pCurrentMesh);
    ctx.pCurrentMesh = pMesh;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------