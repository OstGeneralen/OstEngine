// Kasper "OstGeneralen" Esbjornsson - 2026
#include "IconProvider.h"

#include "EditorContext.h"

#include <imgui.h>

#include <Memory/Memory.h>

// STB IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include "Content/stb_image.h"

using namespace ost;

// ------------------------------------------------------------

IconProvider::IconProvider()
{
    _pixelsPerIcon = 96.0f;
    LoadIconAtlas("Editor/Icons/IconAtlas.png");
    SetIconUV(EIcon::Folder, {0, 0});
    SetIconUV(EIcon::File, {1, 0});
    SetIconUV(EIcon::ImgFile, {2, 0});
    SetIconUV(EIcon::Add, {3, 0});
    SetIconUV(EIcon::Actor, {0, 1});
    SetIconUV(EIcon::Scene, {1, 1});
    SetIconUV(EIcon::Restart, {0, 2});
    SetIconUV(EIcon::Play, {1, 2});
    SetIconUV(EIcon::PlayPause, {2, 2});
    SetIconUV(EIcon::Settings, {3, 2});
}

void ost::IconProvider::DrawIcon(EIcon icon, const Vector2f& size) const
{
    const Vector2f uv = _iconUVs[static_cast<SizeType>(icon)];
    const void* nativeIcon = EditorContext::Get().graphicsEngine.GetResourceManager().GetTexture(_iconTextureHandle).GetNativeResource();
    ImGui::Image((ImTextureRef)(intptr_t)nativeIcon, size, uv, uv + GetIconUVSize());
}

Vector2f ost::IconProvider::GetIconUVSize() const
{
    return {_pixelsPerIcon / _atlasSize.X, _pixelsPerIcon / _atlasSize.Y};
}

void ost::IconProvider::LoadIconAtlas(const char* path)
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

    _iconTextureHandle = EditorContext::Get().graphicsEngine.GetResourceManager().Create(loadedData);
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