// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Asset/DefaultAssets.h"

#include <Math/Color.h>
#include <Memory/Memory.h>

ost::HMaterialInstance ost::DefaultAssetHandle_LitMaterial = {};

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

namespace defaultAssets
{
    TextureCPUData GenerateBaselineData()
    {
        TextureCPUData data;
        data.dimensions = {2, 2};
        data.mipCount = 1;
        data.format = ETextureFormat::RGBAUnorm;
        data.images = List<TextureCPUData::ImageData>(1);
        data.images[0].data = List<Uint8>(sizeof(RGBAColor32) * 4);
        data.images[0].rowPitch = sizeof(RGBAColor32) * 2;
        data.images[0].slicePitch = 0;
        return data;
    }
} // namespace defaultAssets

TextureCPUData ost::GenerateDefaultAssetData_AlbedoTexture()
{
    RGBAColor32 pixels[4];
    pixels[0] = Colors::White;
    pixels[1] = Colors::White;
    pixels[2] = Colors::White;
    pixels[3] = Colors::White;

    TextureCPUData data = defaultAssets::GenerateBaselineData();
    MemCopy(data.images[0].data.GetData(), pixels, sizeof(RGBAColor32) * 4);

    return data;
}

TextureCPUData ost::GenerateDefaultAssetData_NormalTexture()
{
    RGBAColor32 pixels[4];
    pixels[0] = Color(0.5f, 0.5f, 1.0f, 1.0f);
    pixels[1] = Color(0.5f, 0.5f, 1.0f, 1.0f);
    pixels[2] = Color(0.5f, 0.5f, 1.0f, 1.0f);
    pixels[3] = Color(0.5f, 0.5f, 1.0f, 1.0f);

    TextureCPUData data = defaultAssets::GenerateBaselineData();
    MemCopy(data.images[0].data.GetData(), pixels, sizeof(RGBAColor32) * 4);

    return data;
}

TextureCPUData ost::GenerateDefaultAssetData_ORMTexture()
{
    RGBAColor32 pixels[4];
    pixels[0] = Color(0.0f, 1.0f, 0.0f, 1.0f);
    pixels[1] = Color(0.0f, 1.0f, 0.0f, 1.0f);
    pixels[2] = Color(0.0f, 1.0f, 0.0f, 1.0f);
    pixels[3] = Color(0.0f, 1.0f, 0.0f, 1.0f);

    TextureCPUData data = defaultAssets::GenerateBaselineData();
    MemCopy(data.images[0].data.GetData(), pixels, sizeof(RGBAColor32) * 4);

    return data;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------