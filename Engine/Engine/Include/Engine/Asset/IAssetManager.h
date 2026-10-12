// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <filesystem>

#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <GraphicsEngine/Materials/IMaterial.h>
#include <GraphicsEngine/Materials/IMaterialInstance.h>

// ------------------------------------------------------------

namespace ost
{
    class IAssetManager
    {
    public:
        virtual HTexture LoadTextureFromFile(const std::filesystem::path& path) = 0;
        virtual HModel LoadModelFromFile(const std::filesystem::path& path) = 0;
        
        virtual HMaterial CreateMaterial( EMaterialDomain domain, const std::string& materialShader ) = 0; 
        virtual IMaterial& GetMaterial( HMaterial hnd ) = 0;
        
        virtual HMaterialInstance CreateMaterialInstance( HMaterial fromMaterial ) = 0; 
        virtual IMaterialInstance& GetMaterialInstance( HMaterialInstance hnd ) = 0;

        virtual void Release( HTexture h ) = 0;
        virtual void Release( HModel h ) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------