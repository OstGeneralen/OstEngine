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
    LoadImageIcon(EIcon::Folder, "Editor/Icons/icon_folder.png");
    LoadImageIcon(EIcon::File, "Editor/Icons/icon_file.png");
    LoadImageIcon(EIcon::Up, "Editor/Icons/icon_up.png");
}

const ITexture& ost::IconProvider::GetIcon(EIcon icon) const
{
    auto hIcon = _iconTextureHandles[static_cast<SizeType>(icon)];
    return EditorContext::Get().graphicsEngine.GetResourceManager().GetTexture(hIcon);
}

void ost::IconProvider::DrawGUIIcon(EIcon icon, const Vector2f& size) const
{
    const void* nativeIcon = GetIcon(icon).GetNativeResource();
    ImGui::Image((ImTextureRef)(intptr_t)nativeIcon, size);
}

void ost::IconProvider::LoadImageIcon(EIcon icon, const char* path)
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

    MemCopy(imageData.data.GetData(), pixels, w * h * 4);

    stbi_image_free(pixels);

    _iconTextureHandles[static_cast<SizeType>(icon)] = EditorContext::Get().graphicsEngine.GetResourceManager().Create(loadedData);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------