// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"
#include "Engine/Graphics/Material/MaterialInstance.h"

#include <filesystem>

#include <Container/List.h>
#include <GraphicsEngine/GraphicsTypes.h>
#include <GraphicsEngine/Rendering/Vertex.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

namespace ost
{
    using HMaterialClass = TypedIntegerHandle<struct HND_MaterialClass>;

    // ------------------------------------------------------------

    enum class EMaterialLitMode
    {
        Unset,
        Unlit, // No lighting calculations applied
        Lit,   // Lighting calculations applied
    };

    // ------------------------------------------------------------

    enum class EMaterialDomain
    {
        Unset,
        SurfaceOpaque, // During geometry pass, surface vertex, material textures
        PostProcess,   // During scene pass, blit vertex
    };

    // ------------------------------------------------------------

    struct MaterialDesc
    {
        EMaterialLitMode litMode;
        EMaterialDomain domain;
        std::filesystem::path materialShaderPath;
    };

    class MaterialClass : public Asset
    {
    public:
        friend class MaterialManager;

        MaterialClass();
        MaterialClass(const MaterialClass&) = delete;
        MaterialClass(MaterialClass&&) noexcept;

        MaterialClass& operator=(const MaterialClass&) = delete;
        MaterialClass& operator=(MaterialClass&&) noexcept;

        EVertexType GetVertexType() const;

        // BEGIN Asset
        TypeID AssetTypeID() const override
        {
            return TypeID::Get<MaterialClass>();
        }
        // END Asset

    protected:
    private:
        EMaterialLitMode _litMode;
        EMaterialDomain _domain;
        List<MaterialInstance> _instances;

        HShader _vertexShaderHandle;
        HShader _pixelShaderHandle;
        EBlendMode _blendMode;
        EPrimitiveTopology _renderTopology;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------