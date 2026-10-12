// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterial.h"
#include "GraphicsEngine/Materials/MaterialTextureCollection.h"
#include "Materials/MaterialPropertyCollection.h"
#include "Objects/PipelineStateObject.h"

#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    class MaterialInstance;

    struct MaterialPropertiesDesc
    {
        Map<std::string, MaterialProperty> propertyMap;
        SizeType totalSize = 0;
    };

    struct BackendMaterialDesc
    {
        PipelineStateObject pso;
        MaterialPropertiesDesc properties;
        List<MaterialTextureDesc> textureDescs;
    };

    class Material : public IMaterial
    {
    public:
        Material();
        Material(const Material&) = delete;
        Material(Material&&) noexcept;
        ~Material();

        void Create(const BackendMaterialDesc& desc);

        void PopulateInstanceProperties(MaterialInstance& instance) const;
        const SizeType GetPropertiesBufferSize() const;
        const PipelineStateObject& GetPSO() const;

        // BEGIN IMaterial
        IMaterialPropertyCollection& GetPropertyDefaults() override;
        MaterialTextureCollection& GetTextureDefaults() override;
        // END IMaterial

    private:
        PipelineStateObject _pso;
        MaterialPropertyCollection _propertyDefaults;
        MaterialTextureCollection _textureDefaults;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------