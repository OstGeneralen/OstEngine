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
        ctx.RHI.SetPSO(pMaterial->GetPSOFwd());
    }
    if (ctx.pCurrentMaterianInstance != pMaterialInstance)
    {
        ctx.pCurrentMaterianInstance = pMaterialInstance;

        // Update Material Instance Property Buffer
        const auto& propertyBuffer = pMaterialInstance->GetPropertiesBuffer();
        ctx.RHI.UpdateBuffer(propertyBuffer, pMaterialInstance->GetPropertiesData(), pMaterialInstance->GetPropertiesDataSize());
        ctx.RHI.SetBuffer(propertyBuffer, PipelineConstant::Get(EBufferSlot::MaterialProperties), PipelineALL);

        // Set Material Instance Textures
        for (Uint32 i = 0; i < static_cast<Uint32>(MaterialTextureCount); ++i)
        {
            if (pMaterialInstance->Textures().HasTexture(i))
            {
                const Texture& texture = ctx.Resources.Get(pMaterialInstance->Textures().GetTexture(i));
                ctx.RHI.SetTexture(texture, i, EPipelineStage_PS);
            }
        }
    }

    ObjectBufferStructure objectBufferData = {};
    objectBufferData.objectTransform = transform;
    ctx.RHI.UpdateBuffer(objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure));
    ctx.RHI.SetBuffer(objectBuffer, PipelineConstant::Get(EBufferSlot::ObjectBuffer), PipelineALL);
    
    if(ctx.pCurrentModel != pModel)
    {
        ctx.RHI.SetBuffersForIndexed( pModel->vertexBuffer, sizeof(SurfaceVertex), pModel->indexBuffer );
        ctx.pCurrentModel = pModel;
    }

    ctx.RHI.Draw(pMesh->indexCount, pMesh->indexOffset, pMesh->vertexOffset);
}

void ost::RenderCommand::ExecuteDeferred(RenderCommandContext& ctx, const Buffer& objectBuffer) const
{
    const EPipelineStage_ PipelineALL = EPipelineStage_PS | EPipelineStage_VS;

    if (ctx.pCurrentMaterial != pMaterial)
    {
        ctx.pCurrentMaterial = pMaterial;
        ctx.RHI.SetPSO(pMaterial->GetPSODef());
    }
    if (ctx.pCurrentMaterianInstance != pMaterialInstance)
    {
        ctx.pCurrentMaterianInstance = pMaterialInstance;

        // Update Material Instance Property Buffer
        const auto& propertyBuffer = pMaterialInstance->GetPropertiesBuffer();
        ctx.RHI.UpdateBuffer(propertyBuffer, pMaterialInstance->GetPropertiesData(), pMaterialInstance->GetPropertiesDataSize());
        ctx.RHI.SetBuffer(propertyBuffer, PipelineConstant::Get(EBufferSlot::MaterialProperties), PipelineALL);

        // Set Material Instance Textures
        for (Uint32 i = 0; i < static_cast<Uint32>(MaterialTextureCount); ++i)
        {
            if (pMaterialInstance->Textures().HasTexture(i))
            {
                const Texture& texture = ctx.Resources.Get(pMaterialInstance->Textures().GetTexture(i));
                ctx.RHI.SetTexture(texture, i, EPipelineStage_PS);
            }
        }
    }

    ObjectBufferStructure objectBufferData = {};
    objectBufferData.objectTransform = transform;
    ctx.RHI.UpdateBuffer(objectBuffer, &objectBufferData, sizeof(ObjectBufferStructure));
    ctx.RHI.SetBuffer(objectBuffer, PipelineConstant::Get(EBufferSlot::ObjectBuffer), PipelineALL);

    if(ctx.pCurrentModel != pModel)
    {
        ctx.RHI.SetBuffersForIndexed( pModel->vertexBuffer, sizeof(SurfaceVertex), pModel->indexBuffer );
        ctx.pCurrentModel = pModel;
    }

    ctx.RHI.Draw(pMesh->indexCount, pMesh->indexOffset, pMesh->vertexOffset);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------