// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterial.h"
#include "GraphicsEngine/Materials/IMaterialInstance.h"
#include "Materials/MaterialPropertyCollection.h"
#include "Objects/Buffer.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    struct MaterialInstanceDesc
    {
        HMaterial baseMaterialHandle;
        Buffer propertyBuffer;
    };

    class MaterialInstance : public IMaterialInstance
    {
    public:
        MaterialInstance();
        MaterialInstance(const MaterialInstance&) = delete;
        MaterialInstance(MaterialInstance&&) noexcept;
        ~MaterialInstance();

        void Create(const MaterialInstanceDesc& desc);

        HMaterial GetBaseMaterialHandle() const;
        const Buffer& GetPropertiesBuffer() const;

        const Uint8* GetPropertiesData() const;
        SizeType GetPropertiesDataSize() const;

        // BEGIN - IMaterialInstance
        IMaterialPropertyCollection& Properties() override;
        const IMaterialPropertyCollection& Properties() const override;
        MaterialTextureCollection& Textures() override;
        const MaterialTextureCollection& Textures() const override;
        // END - IMaterialInstance

    private:
        HMaterial _baseMaterialHandle;
        MaterialPropertyCollection _properties;
        MaterialTextureCollection _textures;
        Buffer _propertiesBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------