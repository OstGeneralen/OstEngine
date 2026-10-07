// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ImageLoader.h"

#include "Engine/OstEngine.h"

#include <DirectXTex.h>

#include <Utility/Assert.h>
#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

void ImageLoader::Load(const std::string& path, TextureCPUData& into) const
{
    DirectX::TexMetadata metadata;
    DirectX::ScratchImage scratchImg;

    { // Load the file content into blob and then read dds from it
        Blob ddsFileData = FileUtility::ReadFileToBlob(path);
        DirectX::LoadFromDDSMemory(static_cast<const uint8_t*>(ddsFileData.Data()), ddsFileData.Size(), DirectX::DDS_FLAGS_NONE, &metadata, scratchImg);
    }

    OST_ASSERT(metadata.dimension == DirectX::TEX_DIMENSION_TEXTURE2D, "Only supports texture 2D currently");

    // Translate and ensure supported format
    if (metadata.format == DXGI_FORMAT_BC7_TYPELESS)
    {
        metadata.format = DXGI_FORMAT_BC7_UNORM;
    }

    switch (metadata.format)
    {
    case DXGI_FORMAT_BC7_UNORM:
        into.format = ETextureFormat::DDS_BC7;
        break;
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        into.format = ETextureFormat::DDS_BC7_SRGB;
        break;
    default:
        OST_ASSERT(false, "Must be BC7 rgba or srgb");
    }

    into.mipCount = metadata.mipLevels;
    into.dimensions = Vector2u{static_cast<Uint32>(metadata.width), static_cast<Uint32>(metadata.height)};

    // Now we copy across the various image pixel data into the assigned buffers
    into.images = List<TextureCPUData::ImageData>{scratchImg.GetImageCount()};

    for (SizeType imageIndex = 0; imageIndex < into.images.GetSize(); ++imageIndex)
    {
        auto& dxImage = scratchImg.GetImages()[imageIndex];
        auto& cpuDataImage = into.images[imageIndex];

        cpuDataImage.data = List<Uint8>(static_cast<SizeType>(dxImage.slicePitch));
        MemCopy(cpuDataImage.data.GetData(), dxImage.pixels, cpuDataImage.data.GetSize());

        cpuDataImage.rowPitch = dxImage.rowPitch;
        cpuDataImage.slicePitch = dxImage.slicePitch;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------