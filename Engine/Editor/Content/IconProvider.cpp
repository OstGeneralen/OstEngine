// Kasper "OstGeneralen" Esbjornsson - 2026
#include "IconProvider.h"

#include "EditorContext.h"

#include <imgui.h>

#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>
#include <Memory/Memory.h>

// STB IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include "Content/stb_image.h"

using namespace ost;

// ------------------------------------------------------------

IconProvider::IconProvider(IGraphicsResourceManager& gfxResourceManager)
{
    LoadIconAtlas("Editor/Icons/IconAtlas.png", gfxResourceManager);

    SetIconUV(EIcon::Folder, {0, 0});
    SetIconUV(EIcon::File, {1, 0});
    SetIconUV(EIcon::Image, {2, 0});
    SetIconUV(EIcon::Shader, {3, 0});
    SetIconUV(EIcon::Audio, {4, 0});
    SetIconUV(EIcon::Material, {5, 0});
    SetIconUV(EIcon::Actor, {0, 1});
    SetIconUV(EIcon::Model, {1, 1});
    SetIconUV(EIcon::Settings, {2, 1});
}

void ost::IconProvider::DrawIcon(EIcon icon, const Vector2f& size) const
{
    const Vector2f uv = _iconUVs[static_cast<SizeType>(icon)];
    ImGui::Image((ImTextureRef)(intptr_t)_pNativeAtlasTexture, size, uv, uv + GetIconUVSize());
}

Vector2f ost::IconProvider::GetIconUVSize() const
{
    return {_pixelsPerIcon / _atlasSize.X, _pixelsPerIcon / _atlasSize.Y};
}

void ost::IconProvider::LoadIconAtlas(const char* path, IGraphicsResourceManager& resourceManager)
{
    TextureCPUData loadedData;
    loadedData.format = ETextureFormat::RGBAUnorm;
    TextureCPUData::ImageData& imageData = loadedData.images.Add({});
    loadedData.mipCount = 1;

    Int32 w = 0;
    Int32 h = 0;
    Int32 c = 0;
    stbi_uc* pixels = stbi_load(path, &w, &h, &c, 4);

    imageData.slicePitch = 0;
    imageData.rowPitch = w * 4;
    imageData.data = List<Uint8>(w * h * 4);
    loadedData.dimensions = Vector2i{w, h}.VectorCast<Uint32>();

    _atlasSize.X = static_cast<Float32>(w);
    _atlasSize.Y = static_cast<Float32>(h);

    MemCopy(imageData.data.GetData(), pixels, w * h * 4);

    stbi_image_free(pixels);

    auto hTexture = resourceManager.Create(loadedData);
    _pNativeAtlasTexture = resourceManager.GetTexture(hTexture).GetNativeResource();
}

void ost::IconProvider::SetIconUV(EIcon icon, const Vector2u& imageLocation)
{
    const Vector2f pixelLocation = imageLocation.VectorCast<Float32>() * _pixelsPerIcon;
    const Vector2f uv = {pixelLocation.X / _atlasSize.X, pixelLocation.Y / _atlasSize.Y};
    _iconUVs[static_cast<SizeType>(icon)] = uv;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------