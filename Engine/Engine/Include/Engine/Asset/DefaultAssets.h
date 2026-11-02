// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <string_view>

#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <GraphicsEngine/Resources/TextureCPUData.h>

// ------------------------------------------------------------

namespace ost
{
    constexpr static std::string_view DefaultAssetName_AlbedoTexture = "OstEngineDefault/Tex/Albedo";
    constexpr static std::string_view DefaultAssetName_NormalTexture = "OstEngineDefault/Tex/Normal";
    constexpr static std::string_view DefaultAssetName_ORMTexture = "OstEngineDefault/Tex/ORM";

    constexpr static std::string_view DefaultAssetName_CubeMesh = "OstEngineDefault/Msh/Cube";

    constexpr static std::string_view DefaultAssetName_LitMaterial = "OstEngineDefault/Mat/Lit";

    static HMaterialInstance DefaultAssetHandle_LitMaterial;

    extern TextureCPUData GenerateDefaultAssetData_AlbedoTexture();
    extern TextureCPUData GenerateDefaultAssetData_NormalTexture();
    extern TextureCPUData GenerateDefaultAssetData_ORMTexture();
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------