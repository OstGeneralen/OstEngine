// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <GraphicsEngine/GraphicsTypes.h>
#include <GraphicsEngine/Rendering/Vertex.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class MaterialInstance;

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

    class MaterialClass
    {
    public:
        MaterialClass();
        MaterialClass(const MaterialClass&) = delete;
        MaterialClass(MaterialClass&&) noexcept;

        MaterialClass& operator=(const MaterialClass&) = delete;
        MaterialClass& operator=(MaterialClass&&) noexcept;

        EVertexType GetVertexType() const;

        void AddInstance(MaterialInstance& instance);
        void RemoveInstance(MaterialInstance& instance);
        void UpdateInstancePtr(MaterialInstance* oldPtr, MaterialInstance* newPtr);

    protected:
    private:
        EMaterialLitMode _litMode;
        EMaterialDomain _domain;
        List<MaterialInstance*> _instancePtrs;

        HShader _vertexShaderHandle;
        HShader _pixelShaderHandle;
        EBlendState _blendMode;
        EPrimitiveTopology _renderTopology;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------