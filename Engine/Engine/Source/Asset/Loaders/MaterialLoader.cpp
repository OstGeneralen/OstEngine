// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialLoader.h"

#include "Engine/Asset/IAssetManager.h"

#include <fstream>

#include <Container/Map.h>
#include <GraphicsEngine/Materials/IMaterialManager.h>
#include <nlohmann/json.hpp>

// ------------------------------------------------------------

using namespace ost;
using namespace nlohmann;

// ------------------------------------------------------------

HMaterial MaterialLoader::LoadMaterial(const std::string& path, IAssetManager& assets, IMaterialManager& materials)
{
    std::ifstream fs(path);
    json materialJson;
    materialJson << fs;

    MaterialDesc desc;

    const std::string& domainStr = materialJson["domain"].get<std::string>();
    if (domainStr == "surfaceLit")
    {
        desc.domain = EMaterialDomain::SurfaceLit;
    }
    desc.materialShaderPath = materialJson["shader"].get<std::string>();

    return materials.CreateMaterial(desc);
}

HMaterialInstance MaterialLoader::LoadMaterialInstance(const std::string& path, IAssetManager& assets, IMaterialManager& materials)
{
    std::ifstream fs(path);
    json data;
    data << fs;

    HMaterial classHandle = assets.GetHandle<IMaterial>(data["materialClass"].get<std::string>());
    HMaterialInstance createdHandle = materials.CreateInstance(classHandle);
    IMaterialInstance& createdInstance = materials.GetMaterialInstance(createdHandle);

    if (data.contains("textures"))
    {
        for (auto texData : data["textures"])
        {
            HTexture t = assets.Load<HTexture>(texData["texture"].get<std::string>());
            createdInstance.Textures().SetTexture(static_cast<EMaterialTexture>(texData["slot"].get<SizeType>()), t);
        }
    }

    return createdHandle;
}
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------