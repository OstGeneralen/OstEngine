// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/Material.h"

#include <Container/Map.h>
#include <Memory/Blob.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class MaterialFactory
    {
    public:
        MaterialFactory();
        ~MaterialFactory();

        void Initialize(const RenderHardwareInterface& rhi);

        bool CreateMaterial(const MaterialDesc& desc, Material& outMaterial);

    private:
        void ReflectMaterialProperties( const void* pBytecode, SizeType bytecodeSize, Material& intoMaterial );    

        Map<EMaterialDomain, Map<EMaterialShadingModel, Blob>> _rootMaterialSourceCode;
        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------